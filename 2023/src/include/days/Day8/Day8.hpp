#ifndef __DAY8_HPP__
#define __DAY8_HPP__

#include <day.hpp>
#include <stdio.h>

class Day8 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
public:
    void partA() {
        partASolution = 0;
    }
    
    void partB() {
        partBSolution = 0;
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day8() : Day("input/day8.txt") {}
};

#endif