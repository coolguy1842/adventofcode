#ifndef __DAY1_HPP__
#define __DAY1_HPP__

#include <spdlog/spdlog.h>
#include <day.hpp>

#include <vector>
#include <regex>

class Day1 : public AOC::Day {
public:
    int partASolution;
    int partBSolution;

    void partA() {
        std::vector<int> numbers = {};

        for(std::string i : split(this->input, "\n")) {
            std::vector<int> digits = {};

            for(char c : i) {
                if(isdigit(c)) {
                    digits.push_back(c - '0');
                }
            }

            // printf("%d\n", (digits[0] * 10) + digits[digits.size() - 1]);
            // numbers.push_back((digits[0] * 10) + digits[digits.size() - 1]);
        }

        partASolution = 0;
        for(int num : numbers) {
            partASolution += num;
        }
    }
    
    void partB() {
        std::vector<int> numbers = {};

        std::regex first("^.*?(([0-9])|(one|two|three|four|five|six|seven|eight|nine)){1}"); 
        std::regex last(".*(([0-9])|(one|two|three|four|five|six|seven|eight|nine))");

        for(std::string i : split(this->input, "\n")) {
            std::vector<int> digits = {};
            
            std::smatch m; 
            std::regex_search(i, m, first);
            std::smatch m2; 
            std::regex_search(i, m2, last, std::regex_constants::match_any);

            std::string digitStr = m[1];
            digitStr = replace(digitStr, "one", "1");
            digitStr = replace(digitStr, "two", "2");
            digitStr = replace(digitStr, "three", "3");
            digitStr = replace(digitStr, "four", "4");
            digitStr = replace(digitStr, "five", "5");
            digitStr = replace(digitStr, "six", "6");
            digitStr = replace(digitStr, "seven", "7");
            digitStr = replace(digitStr, "eight", "8");
            digitStr = replace(digitStr, "nine", "9");
            
            std::string digitStr2 = m2[1];
            digitStr2 = replace(digitStr2, "one", "1");
            digitStr2 = replace(digitStr2, "two", "2");
            digitStr2 = replace(digitStr2, "three", "3");
            digitStr2 = replace(digitStr2, "four", "4");
            digitStr2 = replace(digitStr2, "five", "5");
            digitStr2 = replace(digitStr2, "six", "6");
            digitStr2 = replace(digitStr2, "seven", "7");
            digitStr2 = replace(digitStr2, "eight", "8");
            digitStr2 = replace(digitStr2, "nine", "9");

            numbers.push_back(((digitStr[0] - '0') * 10) + (digitStr2[0] - '0'));

            printf("%s, %s\n", digitStr.c_str(), digitStr2.c_str());
        }

        partBSolution = 0;
        for(int num : numbers) {
            partBSolution += num;
        }
    }

    void printSolution() {
        spdlog::info("partA: {}", partASolution);
        spdlog::info("partB: {}", partBSolution);
    }

    Day1() : Day("input/day1.txt") {}
};

#endif