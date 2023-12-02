#ifndef __DAY3_HPP__
#define __DAY3_HPP__

#include <spdlog/spdlog.h>
#include <day.hpp>

#include <vector>

class Day3 : public AOC::Day {
private:
    int partASolution;
    int partBSolution;

public:
    void partA() {

    }
    
    void partB() {

    }

    void printSolution(bool partA, bool partB) {
        if(partA) spdlog::info("partA: {}", partASolution);
        if(partB) spdlog::info("partB: {}", partBSolution);
    }

    Day3() : Day("input/day3.txt") {}
};

#endif