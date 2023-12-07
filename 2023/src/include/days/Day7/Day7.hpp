#ifndef __DAY7_HPP__
#define __DAY7_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>
#include <map>

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

const robin_hood::unordered_flat_map<char, size_t> cardStrengths = {
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
};

class Hand {
private:
    std::map<char, size_t> cardsMap;
    std::vector<size_t> sortedValues;
    
    void loadHandType() {
        // all cards are the same so just do five of a kind
        if(sortedValues[0] >= 5) handType = HandType::FIVEOFAKIND;
        // 4 of any card will always be four of a kind
        else if(sortedValues[0] == 4) handType = HandType::FOUROFAKIND;
        // 3 of any card with a pair of the same card is full house
        else if(sortedValues[0] == 3 && sortedValues[1] == 2) handType = HandType::FULLHOUSE;
        // only other one with 3 matching is three of a kind
        else if(sortedValues[0] == 3) handType = HandType::THREEOFAKIND;
        // two different pairs of cards is a two pair
        else if(sortedValues[0] == 2 && sortedValues[1] == 2) handType = HandType::TWOPAIR;
        // only one pair of two dont care about second since the upper if will catch it
        else if(sortedValues[0] == 2) handType = HandType::ONEPAIR;
        // only other option
        else handType = HandType::HIGHCARD;
    }

public:
    HandType handType;
    
    std::string cards;
    size_t bid;

    Hand(const char* cardsC, size_t bid) : cards(cardsC), bid(bid) {
        for(const char& c : cards) {
            if(!cardsMap.contains(c)) cardsMap[c] = 1;
            else cardsMap[c]++;
        }

        for(const auto& pair : cardsMap) {
            sortedValues.push_back(pair.second);
        }

        std::sort(sortedValues.rbegin(), sortedValues.rend());
        loadHandType();
    }

    bool operator>(const Hand& hand) {
        if(this->handType == hand.handType) {
            for(size_t i = 0; i < 5; i++) {
                size_t thisCardValue = cardStrengths.at(this->cards[i]);
                size_t otherCardValue = cardStrengths.at(hand.cards[i]);
                
                if(thisCardValue == otherCardValue) continue;
                return thisCardValue > otherCardValue;
            }
        }
        
        return this->handType > hand.handType;
    }
    
    bool operator<(const Hand& hand) {
        if(this->handType == hand.handType) {
            for(size_t i = 0; i < 5; i++) {
                size_t thisCardValue = cardStrengths.at(this->cards[i]);
                size_t otherCardValue = cardStrengths.at(hand.cards[i]);
                
                if(thisCardValue == otherCardValue) continue;
                return thisCardValue < otherCardValue;
            }
        }
        
        return this->handType < hand.handType;
    }

    bool operator==(const Hand& hand) {
        return this->handType == hand.handType && this->cards == hand.cards;
    }
};

};

namespace PartB {

const robin_hood::unordered_flat_map<char, size_t> cardStrengths = {
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
};

class Hand {
private:
    std::map<char, size_t> cardsMap;
    std::vector<size_t> sortedValues;
    
    HandType checkHandType(std::string hand) {
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
        return HandType::HIGHCARD;
    }

    void loadHandType() {
        size_t jokers = cardsMap['J'];

        if(jokers <= 0) {
            handType = checkHandType(cards);
            return;
        }

        // if 4 jokers all 4 jokers would become the best one so both cases would be 5 of a kind
        if(jokers >= 4) handType = HandType::FIVEOFAKIND;
        else if(jokers == 3) {
            // if the 3 jokers become the other card type it would be 5 of a kind
            if(cardsMap.size() == 2) handType = HandType::FIVEOFAKIND;
            // more than 2 types so it will always be 3 of a kind
            else handType = HandType::THREEOFAKIND;
        }
        else if(jokers == 2) {
            // if the 2 jokers become the other card type it would be 5 of a kind
            if(cardsMap.size() == 2) handType = HandType::FIVEOFAKIND;
            // if the 2 jokers become the other card type with 2 it would be 4 of a kind
            else if(cardsMap.size() == 3) handType = HandType::FOUROFAKIND;
            // only other option is 3 of a kind
            else handType = HandType::THREEOFAKIND;
        }
        else {
            // if the joker becomes the other card type it would be 5 of a kind
            if(cardsMap.size() == 2) {
                handType = HandType::FIVEOFAKIND;
            }
            else if (cardsMap.size() == 3) {
                // if the second most card has an amount of 2 we know that it will become 3 and 2 so it is full house
                if(sortedValues[1] == 2) {
                    handType = HandType::FULLHOUSE;
                }
                else {
                    handType = HandType::FOUROFAKIND;
                }
            }
            // 2 cards are the same so add the joker and it is 3 of a kind
            else if (cardsMap.size() == 4) {
                handType = HandType::THREEOFAKIND;
            }
            // else its just a pair
            else {
                handType = HandType::ONEPAIR;
            }
        }
    }

public:
    HandType handType;
    
    std::string cards;
    size_t bid;

    Hand(const char* cardsC, size_t bid) : cards(cardsC), bid(bid) {
        for(const char& c : cards) {
            if(!cardsMap.contains(c)) cardsMap[c] = 1;
            else cardsMap[c]++;
        }

        for(const auto& pair : cardsMap) {
            sortedValues.push_back(pair.second);
        }

        std::sort(sortedValues.rbegin(), sortedValues.rend());
        loadHandType();
    }

    bool operator>(const Hand& hand) {
        if(this->handType == hand.handType) {
            for(size_t i = 0; i < 5; i++) {
                size_t thisCardValue = cardStrengths.at(this->cards[i]);
                size_t otherCardValue = cardStrengths.at(hand.cards[i]);
                
                if(thisCardValue == otherCardValue) continue;
                return thisCardValue > otherCardValue;
            }
        }
        
        return this->handType > hand.handType;
    }
    
    bool operator<(const Hand& hand) {
        if(this->handType == hand.handType) {
            for(size_t i = 0; i < 5; i++) {
                size_t thisCardValue = cardStrengths.at(this->cards[i]);
                size_t otherCardValue = cardStrengths.at(hand.cards[i]);
                
                if(thisCardValue == otherCardValue) continue;
                return thisCardValue < otherCardValue;
            }
        }
        
        return this->handType < hand.handType;
    }

    bool operator==(const Hand& hand) {
        return this->handType == hand.handType && this->cards == hand.cards;
    }
};

};

class Day7 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    std::vector<PartA::Hand> handsA;
    std::vector<PartB::Hand> handsB;

public:
    void loadHands() {
        // reserve 1 more char for null byte
        char handChars[6];
        size_t bid;

        for(std::string& line : input) {
            sscanf(line.c_str(), "%s %llu", handChars, &bid);

            handsA.push_back(PartA::Hand(handChars, bid));
            handsB.push_back(PartB::Hand(handChars, bid));
        }
    }

    void partA() {
        if(handsA.size() <= 0) loadHands();
        partASolution = 0;

        std::sort(handsA.begin(), handsA.end());

        for(size_t i = 0; i < handsA.size(); i++) {
            partASolution += handsA[i].bid * (i + 1);
        }
    }
    
    void partB() {
        if(handsB.size() <= 0) loadHands();
        partBSolution = 0;

        std::sort(handsB.begin(), handsB.end());

        for(size_t i = 0; i < handsB.size(); i++) {
            partBSolution += handsB[i].bid * (i + 1);
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day7() : Day("input/day7.txt") {}
};

#endif