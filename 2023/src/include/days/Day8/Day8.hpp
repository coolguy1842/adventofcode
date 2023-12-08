#ifndef __DAY8_HPP__
#define __DAY8_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>

class Day8 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    robin_hood::unordered_flat_map<std::string, std::array<std::string, 2>> network;
    std::vector<std::string> partBStarts;
    std::string instructions;

public:
    void loadInput() {
        char instructionsC[513];
        sscanf(input[0].c_str(), "%s\n", instructionsC);

        instructions = std::string(instructionsC);

        // include 4 chars(1 for null byte)
        char location[4], leftDestination[4], rightDestination[4];
        for(size_t i = 2; i < input.size(); i++) {    
            sscanf(input[i].c_str(), "%3s = (%3s, %3s)\n", location, leftDestination, rightDestination);
            network[std::string(location)] = { std::string(leftDestination), std::string(rightDestination) };

            if(location[2] == 'A') {
                partBStarts.push_back(std::string(location));
            }
        }
    }


    size_t findLocation(std::string start, bool partB) {
        size_t out = 0;
        
        std::string current = start;
        while(partB ? current[2] != 'Z' : current != "ZZZ") {
            char instruction = instructions[out % instructions.size()];

            switch(instruction) {
            case 'L': current = network[current][0]; break;
            case 'R': current = network[current][1]; break;
            default: break;
            }

            out++;
        }

        return out;
    }

    void partA() {
        if(network.size() <= 0) loadInput();
        partASolution = findLocation("AAA", false);
    }

    void partB() {
        if(network.size() <= 0) loadInput();

        partBSolution = findLocation(partBStarts[0], true);
        for(std::string& start : partBStarts) {
            partBSolution = std::lcm(partBSolution, findLocation(start, true));
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day8() : Day("input/day8.txt") {}
};

#endif