#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdio>

#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>

Day::Day() : AOCUtil::IDay(dayInput) {}
#define COMP_STR(str1, str2) strncmp(str1, str2, std::min(strlen(str1), strlen(str2))) 

size_t partFunc(const std::string& str, bool partB = false) {
    size_t pos = -1, out = 0;
    bool acceptMuls = true;

    while((pos = str.find("(", pos + 1)) != std::string::npos) {
        if(partB && !acceptMuls && COMP_STR(&str[pos - 2], "do") == 0) {
            if(str[pos + 1] != ')') {
                continue;
            }

            acceptMuls = true;
        }
        else if(partB && acceptMuls && COMP_STR(&str[pos - 5], "don't") == 0) {
            if(str[pos + 1] != ')') {
                continue;
            }

            acceptMuls = false;
        }
        else if(acceptMuls && COMP_STR(&str[pos - 3], "mul") == 0) {
            size_t left, right;
            int read;

            int res = sscanf(&str[pos + 1], "%zu,%zu%n", &left, &right, &read);
            if(res != 2 || str[pos + read + 1] != ')') {
                continue;
            }

            out += left * right;
        }
    }

    return out;
}

size_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text); }
void Day::partB() { bSolution = partFunc(input.text, true); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}