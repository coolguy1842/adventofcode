#ifndef __DAY4_HPP__
#define __DAY4_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>

struct Card {
    int number;

    robin_hood::unordered_flat_set<int> numbers;
    robin_hood::unordered_flat_set<int> winningNumbers;
};

class Day4 : public AOC::Day {
private:
    int partASolution;
    int partBSolution;
    
    std::vector<Card> cards;

public:
    void loadCards() {
        cards.clear();

        for(std::string& line : this->input) {
            Card card;

            int rest;
            sscanf(line.c_str(), "Card %d: %n", &(card.number), &rest);

            std::vector<std::string> parts = split(std::string(line.c_str() + rest), " | ");
            for(std::string number : split(parts[0], " ")) {
                if(number.size() <= 0) continue;

                card.numbers.emplace(atoi(number.c_str()));
            }

            for(std::string number : split(parts[1], " ")) {
                if(number.size() <= 0) continue;

                card.winningNumbers.emplace(atoi(number.c_str()));
            }

            cards.push_back(card);
        }
    }


    void partA() {
        if(cards.size() <= 0) loadCards();
        partASolution = 0;

        for(const Card& card : cards) {
            int value = 0;
            
            for(int number : card.numbers) {
                if(!card.winningNumbers.contains(number)) continue;

                if(value == 0) value = 1;
                else value *= 2;
            }

            partASolution += value;
        }
    }

    std::vector<Card> partBFunc(std::vector<Card> list) {
        std::vector<Card> out;

        for(const Card& card : list) {
            int value = 0;

            for(int number : card.numbers) {
                if(!card.winningNumbers.contains(number)) continue;
                
                value++;
            }
            
            for(int i = 0; i < value; i++) {
                out.push_back(cards[card.number + i]);
            }
        }

        return out;
    }
    
    void partB() {
        if(cards.size() <= 0) loadCards();
        partBSolution = cards.size();
        std::vector<Card> temp = cards;
        
        while((temp = partBFunc(temp)).size() > 0) {
            partBSolution += temp.size();
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %d\n", partASolution);
        if(partB) printf("partB: %d\n", partBSolution);
    }

    Day4() : Day("input/day4.txt") {}
};

#endif