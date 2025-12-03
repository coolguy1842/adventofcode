#include <Days/Day03.hpp>
#include <Input/Day03.hpp>
#include <Util/StringUtil.hpp>
#include <cstdint>
#include <cstring>
#include <string>

void Day3::partA() {
    char left  = '0';
    char right = '0';

    for(size_t i = 0; i <= input.size(); i++) {
        const char& c = input[i];
        if(c == '\n' || c == '\0') {
            aSolution += ((left - '0') * 10) + (right - '0');

            left  = '0';
            right = '0';
            continue;
        }

        if(right > left) {
            left  = right;
            right = c;
        }
        else if(c > right) {
            right = c;
        }
    }
}

void Day3::partB() {
    constexpr int64_t numBatteries = 12;

    const char *str = input.c_str(), *endPos = input.c_str() + input.size();
    // all expected to be the same length
    int64_t strLen = strchrnul(str, '\n') - str;

    do {
        char batteries[numBatteries];
        int64_t batteriesSet = -1;

        for(int64_t i = 0; i < strLen; i++) {
            const char& c = str[i];

            int64_t batteryMin = numBatteries - std::min(strLen - i, numBatteries);
            for(int64_t battery = batteryMin; battery < numBatteries; battery++) {
                char& batteryValue = batteries[battery];
                if(batteriesSet < battery || c > batteryValue) {
                    batteryValue = c;
                    batteriesSet = battery;

                    break;
                }
            }
        }

        size_t out = 0;
        for(size_t i = 0; i < numBatteries; i++) {
            out *= 10;
            out += batteries[i] - '0';
        }

        bSolution += out;

        str += strLen + 1;
    } while(str != endPos + 1);
}

void Day3::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}