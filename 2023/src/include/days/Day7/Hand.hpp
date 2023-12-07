#ifndef __HAND_HPP__
#define __HAND_HPP__

#include <robin_hood.hpp>
#include <vector>

enum HandType {
    HIGHCARD = 0,
    ONEPAIR,
    TWOPAIR,
    THREEOFAKIND,
    FULLHOUSE,
    FOUROFAKIND,
    FIVEOFAKIND,
};

namespace PartA {

class Hand {
protected:
    virtual robin_hood::unordered_flat_map<char, size_t> cardStrengths() {
        return robin_hood::unordered_flat_map<char, size_t>({
            { '2', 0  },
            { '3', 1  },
            { '4', 2  },
            { '5', 3  },
            { '6', 4  },
            { '7', 5  },
            { '8', 6  },
            { '9', 7  },
            { 'T', 8  },
            { 'J', 9 },
            { 'Q', 10 },
            { 'K', 11 },
            { 'A', 12 }
        });
    }

    robin_hood::unordered_flat_map<char, size_t> cardsMap;
    std::vector<size_t> sortedValues;

    virtual HandType getHandType() {
        // all cards are the same so just do five of a kind
        if(sortedValues[0] >= 5) return HandType::FIVEOFAKIND;
        // 4 of any card will always be four of a kind
        else if(sortedValues[0] == 4) return HandType::FOUROFAKIND;
        // 3 of any card with a pair of the same card is full house
        else if(sortedValues[0] == 3 && sortedValues[1] == 2) return HandType::FULLHOUSE;
        // only other one with 3 matching is three of a kind
        else if(sortedValues[0] == 3) return HandType::THREEOFAKIND;
        // two different pairs of cards is a two pair
        else if(sortedValues[0] == 2 && sortedValues[1] == 2) return HandType::TWOPAIR;
        // only one pair of two dont care about second since the upper if will catch it
        else if(sortedValues[0] == 2) return HandType::ONEPAIR;
        // only other option
        else return HandType::HIGHCARD;
    }

    void loadData() {
        for(const char& c : cards) {
            if(!cardsMap.contains(c)) cardsMap[c] = 1;
            else cardsMap[c]++;
        }

        for(const auto& pair : cardsMap) {
            sortedValues.push_back(pair.second);
        }

        std::sort(sortedValues.rbegin(), sortedValues.rend());
    }

public:
    HandType handType;
    
    std::string cards;
    size_t bid;

    Hand(const char* cardsC, size_t bid, bool loadHand = true) : cards(cardsC), bid(bid) {
        loadData();
        if(loadHand) handType = getHandType();
    }

    std::partial_ordering operator<=>(const Hand& hand) {
        if(this->handType == hand.handType) {
            const auto strengths = cardStrengths();
            for(size_t i = 0; i < 5; i++) {
                size_t thisCardValue = strengths.at(this->cards[i]);
                size_t otherCardValue = strengths.at(hand.cards[i]);
                
                if(thisCardValue == otherCardValue) continue;
                return thisCardValue < otherCardValue ? std::partial_ordering::less : std::partial_ordering::greater;
            }
        }
        
        return this->handType < hand.handType ? std::partial_ordering::less : std::partial_ordering::greater;
    }
};

};

namespace PartB {

class Hand : public PartA::Hand {
private:
    robin_hood::unordered_flat_map<char, size_t> cardStrengths() {
        return robin_hood::unordered_flat_map<char, size_t>({
            { 'J', 0 },
            { '2', 1  },
            { '3', 2  },
            { '4', 3  },
            { '5', 4  },
            { '6', 5  },
            { '7', 6  },
            { '8', 7  },
            { '9', 8  },
            { 'T', 9  },
            { 'Q', 10 },
            { 'K', 11 },
            { 'A', 12 }
        });
    }

    HandType getHandType() {
        size_t jokers = cardsMap['J'];

        if(jokers <= 0) {
            return PartA::Hand::getHandType();
        }

        // if 4 jokers all 4 jokers would become the best one so both cases would be 5 of a kind
        if(jokers >= 4) return HandType::FIVEOFAKIND;
        else if(jokers == 3) {
            // if the 3 jokers become the other card type it would be 5 of a kind
            if(cardsMap.size() == 2) return HandType::FIVEOFAKIND;
            // more than 2 types so it will always be 3 of a kind
            else return HandType::THREEOFAKIND;
        }
        else if(jokers == 2) {
            // if the 2 jokers become the other card type it would be 5 of a kind
            if(cardsMap.size() == 2) return HandType::FIVEOFAKIND;
            // if the 2 jokers become the other card type with 2 it would be 4 of a kind
            else if(cardsMap.size() == 3) return HandType::FOUROFAKIND;
            // only other option is 3 of a kind
            else return HandType::THREEOFAKIND;
        }
        
        // only one joker
        // if the joker becomes the other card type it would be 5 of a kind
        if(cardsMap.size() == 2) return HandType::FIVEOFAKIND;
        else if (cardsMap.size() == 3) {
            // if the second most card has an amount of 2 we know that it will become 3 and 2 so it is full house
            if(sortedValues[1] == 2) return HandType::FULLHOUSE;
            else return HandType::FOUROFAKIND;
        }
        // 2 cards are the same so add the joker and it is 3 of a kind
        else if (cardsMap.size() == 4) return HandType::THREEOFAKIND;
        // else its just a pair
        
        return HandType::ONEPAIR;
    }

public:
    Hand(const char* cardsC, size_t bid) : PartA::Hand(cardsC, bid, false) {
        handType = getHandType();
    }
};

};

#endif