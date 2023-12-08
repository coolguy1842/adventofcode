#ifndef __DAY9_HPP__
#define __DAY9_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>

class Day9 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
public:
    void partA() {
        
    }

    void partB() {
        
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day9() : Day("input/day9.txt") {}
};

#endif