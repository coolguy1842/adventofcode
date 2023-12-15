#ifndef __DAYNUM_HPP__
#define __DAYNUM_HPP__

#include <day.hpp>
#include <stdio.h>

class DayNUM : public AOC::Day {
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

    DayNUM() : Day("input/dayNUM.txt") {}
};

#endif