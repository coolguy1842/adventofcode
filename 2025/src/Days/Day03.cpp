#include <Days/Day03.hpp>
#include <Input/Day03.hpp>
#include <Util/StringUtil.hpp>
#include <cstring>
#include <string>

void Day3::partA() {
    StringUtil::split(input, '\n', [this](const std::string& str) {
        char left  = '0';
        char right = '0';

        for(const char& c : str) {
            if(right > left) {
                left  = right;
                right = c;
            }
            else if(c > right) {
                right = c;
            }
        }

        aSolution += ((left - '0') * 10) + (right - '0');
    });
}

void Day3::partB() {
    StringUtil::split(input, '\n', [this](const std::string& str) {
        char batteries[12];
        memset(batteries, '0', sizeof(batteries));

        for(size_t i = 0; i < str.size(); i++) {
            const char& c = str[i];

            size_t batteryMin = sizeof(batteries) - std::min(str.size() - i, sizeof(batteries));
            for(size_t battery = batteryMin; battery < sizeof(batteries); battery++) {
                char& batteryValue = batteries[battery];
                if(c > batteryValue) {
                    batteryValue = c;
                    memset(batteries + battery + 1, '0', sizeof(batteries) - (battery + 1));
                    break;
                }
            }
        }

        size_t out = 0;
        for(size_t i = 0; i < sizeof(batteries); i++) {
            out *= 10;
            out += batteries[i] - '0';
        }

        bSolution += out;
    });
}

void Day3::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}