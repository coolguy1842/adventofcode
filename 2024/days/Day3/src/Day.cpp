#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdio>

#include <regex>
#include <spdlog/spdlog.h>

Day::Day() : AOCUtil::IDay(dayInput) {}

size_t aSolution = 0, bSolution = 0;
void Day::partA() {
    auto exp = std::regex(R"((mul\(\d+,\d+\)))");

    auto words_begin = std::sregex_iterator(input.text.begin(), input.text.end(), exp);
    auto words_end = std::sregex_iterator();

    for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::string match = i->str();

        size_t left, right;
        sscanf(match.c_str(), "mul(%zu,%zu)", &left, &right);
        aSolution += left * right;
    }
}

void Day::partB() {
    auto exp = std::regex(R"(((mul\(\d+,\d+\))|(do(n't)?\(\))))");

    auto words_begin = std::sregex_iterator(input.text.begin(), input.text.end(), exp);
    auto words_end = std::sregex_iterator();

    bool acceptMuls = true;
    for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::string match = i->str();
        if(match == "do()") {
            acceptMuls = true;
        }
        else if(match == "don't()") {
            acceptMuls = false;
        }
        else if(acceptMuls) {
            size_t left, right;
            sscanf(match.c_str(), "mul(%zu,%zu)", &left, &right);
            
            bSolution += left * right;
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}