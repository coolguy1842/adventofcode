#include <Days/DayN.hpp>
#include <Input/DayN.hpp>
#include <Util/StringUtil.hpp>

void DayN::partA() {
}

void DayN::partB() {
}

void DayN::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: \n");
    }

    if(parts.test(B)) {
        printf("Part B: \n");
    }
}