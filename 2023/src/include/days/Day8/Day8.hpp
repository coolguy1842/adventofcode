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
        instructions = input[0];

        // each are 4 bytes(1 byte reserved for null byte)
        char location[4], leftDestination[4], rightDestination[4];
        location[3] = leftDestination[3] = rightDestination[3] = 0;

        for(size_t i = 2; i < input.size(); i++) {    
            const std::string& line = input[i];

            memcpy(location, line.c_str(), 3);
            memcpy(leftDestination, line.c_str() + strlen("aaa = ("), 3);
            memcpy(rightDestination, line.c_str() + strlen("aaa = (zzz, "), 3);

            network[location] = { leftDestination, rightDestination };

            if(location[2] == 'A') {
                partBStarts.push_back(location);
            }
        }
    }


    size_t findLocation(const std::string& start, const bool partB) {
        size_t out = 0;
        
        std::string current = start;
        while(partB ? current[2] != 'Z' : current != "ZZZ") {
            char instruction = instructions[out % (instructions.length() - 1)];
            
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
        for(size_t i = 1; i < partBStarts.size(); i++) {
            partBSolution = std::lcm(partBSolution, findLocation(partBStarts[i], true));
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day8() : Day("input/day8.txt") {}
};

#endif