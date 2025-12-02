#include <Days/Day02.hpp>
#include <Input/Day02.hpp>
#include <Util/StringUtil.hpp>
#include <cstdint>
#include <cstdio>
#include <string>

void Day2::partA() {
    auto isInvalid = [](uint64_t id) {
        std::string str = std::to_string(id);

        for(size_t i = 1; i <= str.size() / 2; i++) {
            if(str.substr(0, i) == str.substr(i, str.size())) {
                return true;
            }
        }

        return false;
    };

    StringUtil::split(input, ",", [this, &isInvalid](std::string range) {
        uint64_t start, end;
        sscanf(range.c_str(), "%lu-%lu", &start, &end);

        for(uint64_t id = start; id <= end; id++) {
            if(isInvalid(id)) {
                aSolution += id;
            }
        }
    });
}

void Day2::partB() {
    auto isInvalid = [](uint64_t id) {
        std::string str = std::to_string(id);

        for(size_t i = 1; i <= str.size() / 2; i++) {
            std::string first = str.substr(0, i);

            bool invalid = true;
            for(size_t j = i; j < str.size(); j += i) {
                std::string second = str.substr(j, i);

                if(first != second) {
                    invalid = false;
                    break;
                }
            }

            if(invalid) {
                return true;
            }
        }

        return false;
    };

    StringUtil::split(input, ",", [this, &isInvalid](std::string range) {
        uint64_t start, end;
        sscanf(range.c_str(), "%lu-%lu", &start, &end);

        for(uint64_t id = start; id <= end; id++) {
            if(isInvalid(id)) {
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