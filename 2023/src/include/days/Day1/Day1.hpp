#ifndef __DAY1_HPP__
#define __DAY1_HPP__

#include <stdio.h>
#include <day.hpp>

#include <robin_hood.hpp>

#include <vector>
#include <regex>

class Day1 : public AOC::Day {
private:
    int partASolution;
    int partBSolution;
    
    const robin_hood::unordered_flat_map<std::string, int> strToNumber = {
        { "one",   1 },
        { "two",   2 },
        { "three", 3 },
        { "four",  4 },
        { "five",  5 },
        { "six",   6 },
        { "seven", 7 },
        { "eight", 8 },
        { "nine",  9 },
    };

public:
    void partA() {
        std::regex re("(\\d)");
        partASolution = 0;

        for(const std::string& line : this->input) { 
            std::vector<int> digits = {};
            
            std::smatch res;
            std::string str = line;

            while(std::regex_search(str, res, re)) {
                digits.push_back(res.str(0)[0] - '0');
                str = res.suffix().str();
            }

            partASolution += (digits[0] * 10) + digits[digits.size() - 1];
        }
    }
    
    void partB() {
        partBSolution = 0;
        std::regex re("(\\d|one|two|three|four|five|six|seven|eight|nine)");
    
        for(std::string line : this->input) {
            std::vector<int> digits = {};
            
            std::cmatch res;
            const char* str = line.c_str();
            while(std::regex_search(str, res, re)) {
                std::string num = res.str(0);

                if(isdigit(num[0])) digits.push_back(num[0] - '0');
                else digits.push_back(strToNumber.at(num));
                
                str++;
            }

            partBSolution += (digits[0] * 10) + digits[digits.size() - 1];
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %d\n", partASolution);
        if(partB) printf("partB: %d\n", partBSolution);
    }

    Day1() : Day("input/day1.txt") {}
};

#endif