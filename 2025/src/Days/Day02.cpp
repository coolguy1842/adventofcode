#include <Days/Day02.hpp>
#include <Input/Day02.hpp>
#include <Util/StringUtil.hpp>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>

bool isValidA(uint64_t id) {
    std::string str = std::to_string(id);
    // if odd then it cant be invalid
    if(str.size() & 1) {
        return true;
    }

    return strncmp(str.c_str(), str.c_str() + (str.size() / 2), str.size() / 2) != 0;
}

bool isValidB(uint64_t id) {
    std::string str = std::to_string(id);

    for(size_t i = 1; i <= str.size() / 2; i++) {
        for(size_t j = i; j < str.size(); j += i) {
            if(strncmp(str.c_str(), str.c_str() + j, i) != 0) {
                goto valid;
            }
        }

        return false;
    valid:
    }

    return true;
}

uint64_t runPart(const std::function<bool(uint64_t)>& func) {
    uint64_t out = 0;

    const char* str = input.c_str() - 1;
    char* endPtr;

    do {
        uint64_t start = std::strtoul(str + 1, &endPtr, 10);
        uint64_t end   = std::strtoul(endPtr + 1, &endPtr, 10);

        for(uint64_t id = start; id <= end; id++) {
            if(!func(id)) {
                out += id;
            }
        }

        str = endPtr;
    } while(*str);

    return out;
}

void Day2::partA() { aSolution = runPart(isValidA); }
void Day2::partB() { bSolution = runPart(isValidB); }

void Day2::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}