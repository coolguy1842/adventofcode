#include <Days/DayN.hpp>
#include <Input/DayN.hpp>
#include <Util/StringUtil.hpp>
#include <spdlog/spdlog.h>

void DayN::partA() {
}

void DayN::partB() {
}

void DayN::printSolutions(std::bitset<2> parts) {
    if(parts.test(A)) {
        spdlog::info("Part A: {}", aSolution);
    }

    if(parts.test(B)) {
        spdlog::info("Part B: {}", bSolution);
    }
}