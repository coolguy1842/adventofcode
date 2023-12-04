#ifndef __DAY4_HPP__
#define __DAY4_HPP__

#include <day.hpp>
#include <stdio.h>

class Day4 : public AOC::Day {
private:
    int partASolution;
    int partBSolution;
    
public:
    void partA() {
    
    }
    
    void partB() {
    
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %d\n", partASolution);
        if(partB) printf("partB: %d\n", partBSolution);
    }

    Day4() : Day("input/day4.txt") {}
};

#endif