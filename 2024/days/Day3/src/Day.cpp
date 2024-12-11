#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdio>

#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>

Day::Day() : AOCUtil::IDay(dayInput) {} 

uint64_t partFunc(const std::string& str, bool partB = false) {
    const char *strPtr = str.c_str(), *ptr = strPtr - 1;
    
    uint64_t out = 0;
    bool acceptMuls = true;

    while((ptr = strstr(ptr + 1, "("))) {
        if(partB && !acceptMuls && strncmp(ptr - 2, "do()", 4) == 0) {
            acceptMuls = true;
        }
        else if(partB && acceptMuls && strncmp(ptr - 5, "don't()", 7) == 0) {
            acceptMuls = false;
        }
        else if(acceptMuls && strncmp(ptr - 3, "mul", 3) == 0) {
            uint64_t left, right;
            char endChar;

            if(sscanf(ptr + 1, "%lu,%lu%c", &left, &right, &endChar) == 3 && endChar == ')') {
                out += left * right;
            }
        }
    }

    return out;
}

uint64_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text); }
void Day::partB() { bSolution = partFunc(input.text, true); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}