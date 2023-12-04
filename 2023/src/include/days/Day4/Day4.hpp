#ifndef __DAY4_HPP__
#define __DAY4_HPP__

#include <spdlog/spdlog.h>
#include <day.hpp>

#include <robin_hood.hpp>

#include <vector>
#include <regex>

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
        if(partA) spdlog::info("partA: {}", partASolution);
        if(partB) spdlog::info("partB: {}", partBSolution);
    }

    Day4() : Day("input/day4.txt") {}
};

#endif