#include <Days/Day02.hpp>
#include <Input/Day02.hpp>
#include <Util/MathUtil.hpp>
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
    size_t halfSize = str.size() / 2;

    return strncmp(str.c_str(), str.c_str() + halfSize, halfSize) != 0;
}

bool isValidB(uint64_t id) {
    std::string str = std::to_string(id);

    for(size_t i = 1; i <= str.size() / 2; i++) {
        // if strsize isnt a multiple of the pattern then skip
        if(str.size() % i != 0) {
            continue;
        }

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

void getRanges(const std::function<void(uint64_t, uint64_t)>& loopFunc) {
    char* ptr = const_cast<char*>(input.c_str());

    do {
        uint64_t start = std::strtoul(ptr, &ptr, 10);
        uint64_t end   = std::strtoul(ptr + 1, &ptr, 10);

        loopFunc(start, end);
    } while(*ptr++);
}

void Day2::partA() {
    getRanges([this](uint64_t start, uint64_t end) {
        for(uint64_t id = start; id <= end; id++) {
            // skip to nearest power of 10 if uneven length
            uint8_t log = MathUtil::quickLog10(id);
            if(log & 1) {
                id = MathUtil::quickPow<10>(log);
            }

            if(!isValidA(id)) {
                aSolution += id;
            }
        }
    });
}

void Day2::partB() {
    getRanges([this](uint64_t start, uint64_t end) {
        for(uint64_t id = start; id <= end; id++) {
            if(!isValidB(id)) {
                bSolution += id;
            }
        }
    });
}

void Day2::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}