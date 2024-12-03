#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdio>

#include <regex>
#include <spdlog/spdlog.h>

Day::Day() : AOCUtil::IDay(dayInput) {}

size_t aSolution = 0, bSolution = 0;
void Day::partA() {
    std::regex exp(R"((mul\(\d+,\d+\)))");
    
    for(std::sregex_iterator it = std::sregex_iterator(input.text.begin(), input.text.end(), exp); it != std::sregex_iterator(); it++) {
        size_t left, right;

        sscanf(it->str().c_str(), "mul(%zu,%zu)", &left, &right);
        aSolution += left * right;
    }
}

void Day::partB() {
    std::regex exp(R"(((mul\(\d+,\d+\))|(do(n't)?\(\))))");

    bool acceptMuls = true;
    for(std::sregex_iterator it = std::sregex_iterator(input.text.begin(), input.text.end(), exp); it != std::sregex_iterator(); it++) {
        std::string match = it->str();

        switch(match[0]) {
        case 'd': acceptMuls = match.size() == 4; break;
        case 'm':
            if(!acceptMuls) break;

            size_t left, right;
            sscanf(match.c_str(), "mul(%zu,%zu)", &left, &right);
            
            bSolution += left * right;

            break;
        default: break;
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}