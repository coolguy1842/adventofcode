#ifndef __DAY2_HPP__
#define __DAY2_HPP__

#include <spdlog/spdlog.h>
#include <day.hpp>

#include <vector>
#include <regex>

class Day2 : public AOC::Day {
private:
    int partASolution;
    int partBSolution;

public:
    void partA() {

    }
    
    void partB() {

    }

    void printSolution(bool partA, bool partB) {
        if(partA) spdlog::info("partA: ");
        if(partB) spdlog::info("partB: ");
    }

    Day2() : Day("input/day1.txt") {}
};

#endif