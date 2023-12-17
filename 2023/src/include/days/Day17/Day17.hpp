#ifndef __DAY17_HPP__
#define __DAY17_HPP__

#include <day.hpp>
#include <stdio.h>

class Day17 : public AOC::Day {
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

    Day17() : Day("input/day17.txt") {}
};

#endif