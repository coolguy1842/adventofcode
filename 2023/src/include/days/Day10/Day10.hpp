#ifndef __DAY10_HPP__
#define __DAY10_HPP__

#include <day.hpp>
#include <stdio.h>

class Day10 : public AOC::Day {
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
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day10() : Day("input/day10.txt") {}
};

#endif