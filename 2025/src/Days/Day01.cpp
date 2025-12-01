#include <Days/Day01.hpp>
#include <Input/Day01.hpp>
#include <Util/StringUtil.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>

const int32_t dialMax = 100;
void Day1::partA() {
    int32_t dial = 50;

    for(std::string line : StringUtil::split(input, "\n")) {
        int32_t moveBy;
        sscanf(line.c_str(), "%*c%d", &moveBy);

        dial += moveBy * (line[0] == 'L' ? -1 : 1);

        printf("dial: %d\n", dial);
        if(dial % dialMax == 0) {
            aSolution++;
        }
    }
}

void Day1::partB() {
    int32_t dial = 50;

    for(std::string line : StringUtil::split(input, "\n")) {
        int32_t moveBy;
        sscanf(line.c_str(), "%*c%d", &moveBy);

        int direction = line[0] == 'L' ? -1 : 1;
        for(int32_t i = 0; i < moveBy; i++) {
            dial += direction;

            if(dial % dialMax == 0) {
                bSolution++;
            }
        }
    }
}

void Day1::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %d\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %d\n", bSolution);
    }
}