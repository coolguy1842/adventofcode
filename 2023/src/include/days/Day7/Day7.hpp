#ifndef __DAY7_HPP__
#define __DAY7_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>
#include <map>


#include "Hand.hpp"

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
            sscanf(line.c_str(), "%5s %zu", handChars, &bid);

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
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day7() : Day("input/day7.txt") {}
};

#endif