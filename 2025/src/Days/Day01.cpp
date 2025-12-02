#include <Days/Day01.hpp>
#include <Input/Day01.hpp>
#include <Util/StringUtil.hpp>

constexpr int32_t dialMax = 100;
void Day1::partA() {
    const char* str = input.c_str();
    char* end;

    int32_t dial = 50;
    do {
        dial += strtol(str + 1, &end, 10) * (str[0] == 'R' ? 1 : -1);
        if(dial % dialMax == 0) {
            aSolution++;
        }

        str = end + 1;
    } while(*end);
}

void Day1::partB() {
    const char* str = input.c_str();
    char* end;

    int32_t dial = 50;
    do {
        int8_t dir     = str[0] == 'R' ? 1 : -1;
        int32_t target = dial + (strtol(str + 1, &end, 10) * dir);

        for(; dial != target; dial += dir) {
            if(dial % dialMax == 0) {
                bSolution++;
            }
        }

        str = end + 1;
    } while(*end);
}

void Day1::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %d\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %d\n", bSolution);
    }
}