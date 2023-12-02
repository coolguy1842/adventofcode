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
        const int maxRed = 12;
        const int maxGreen = 13;
        const int maxBlue = 14;

        partASolution = 0;

        for(std::string line : input) {
            std::vector<std::string> splitStr = split(line, ": ");
            int gameID = atoi(split(splitStr[0], " ")[1].c_str());

            std::vector<std::string> sets = split(splitStr[1], "; ");

            int maxRedUsed = 0;
            int maxBlueUsed = 0;
            int maxGreenUsed = 0;

            for(std::string set : sets) {
                std::vector<std::string> cubes = split(set, ", ");

                for(std::string cube : cubes) {
                    std::vector<std::string> info = split(cube, " ");
                    std::string colour = info[1];
                    int count = atoi(info[0].c_str());

                    if(colour == "red") maxRedUsed = std::max(maxRedUsed, count);
                    else if(colour == "blue") maxBlueUsed = std::max(maxBlueUsed, count);
                    else if(colour == "green") maxGreenUsed = std::max(maxGreenUsed, count);
                }
            }

            if(maxRedUsed > maxRed || maxBlueUsed > maxBlue || maxGreenUsed > maxGreen) {
                printf("red: %d, green: %d, blue: %d\n", maxRedUsed, maxBlueUsed, maxGreenUsed);

                continue;
            }

            partASolution += gameID;
        }
    }
    
    void partB() {
        partBSolution = 0;

        for(std::string line : input) {
            std::vector<std::string> splitStr = split(line, ": ");
            int gameID = atoi(split(splitStr[0], " ")[1].c_str());

            std::vector<std::string> sets = split(splitStr[1], "; ");

            int maxRedUsed = 0;
            int maxBlueUsed = 0;
            int maxGreenUsed = 0;

            for(std::string set : sets) {
                std::vector<std::string> cubes = split(set, ", ");

                for(std::string cube : cubes) {
                    std::vector<std::string> info = split(cube, " ");
                    std::string colour = info[1];
                    int count = atoi(info[0].c_str());

                    if(colour == "red") maxRedUsed = std::max(maxRedUsed, count);
                    else if(colour == "blue") maxBlueUsed = std::max(maxBlueUsed, count);
                    else if(colour == "green") maxGreenUsed = std::max(maxGreenUsed, count);
                }
            }

            partBSolution += maxRedUsed * maxGreenUsed * maxBlueUsed;
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) spdlog::info("partA: {}", partASolution);
        if(partB) spdlog::info("partB: {}", partBSolution);
    }

    Day2() : Day("input/day2.txt") {}
};

#endif