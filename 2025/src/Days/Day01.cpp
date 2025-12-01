#include <Days/Day01.hpp>
#include <Input/Day01.hpp>
#include <Util/StringUtil.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>

constexpr int32_t dialMax = 100;
void Day1::partA() {
    int32_t dial = 50;
    StringUtil::split(input, "\n", [this, &dial](const std::string& line) {
        dial += atoi(line.c_str() + 1) * (line[0] == 'L' ? -1 : 1);

        if(dial % dialMax == 0) {
            aSolution++;
        }
    });
}

void Day1::partB() {
    int32_t dial = 50;
    StringUtil::split(input, "\n", [this, &dial](const std::string& line) {
        int32_t dir    = line[0] == 'L' ? -1 : 1;
        int32_t target = dial + (atoi(line.c_str() + 1) * dir);

        for(; dial != target; dial += dir) {
            if(dial % dialMax == 0) {
                bSolution++;
            }
        }
    });
}

void Day1::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %d\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %d\n", bSolution);
    }
}