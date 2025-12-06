#include <Days/Day06.hpp>
#include <Input/Day06.hpp>
#include <Util/StringUtil.hpp>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

void Day6::partA() {
    std::vector<std::string> split = StringUtil::split(input, '\n');
    std::vector<std::vector<uint64_t>> numbers(StringUtil::split(split[0], ' ').size());

    for(size_t i = 0; i < split.size() - 1; i++) {
        std::vector<std::string> splitNumbers = StringUtil::split(split[i], ' ');
        for(size_t j = 0; j < splitNumbers.size(); j++) {
            numbers[j].push_back(strtoul(splitNumbers[j].c_str(), NULL, 10));
        }
    }

    std::vector<std::string> operations = StringUtil::split(split.back(), ' ');
    for(size_t i = 0; i < operations.size(); i++) {
        const char& operation = operations[i][0];
        uint64_t out          = (operation == '*' ? 1 : 0);

        for(const uint64_t& num : numbers[i]) {
            switch(operation) {
            case '+': out += num; break;
            case '*': out *= num; break;
            }
        }

        aSolution += out;
    }
}

void Day6::partB() {
    std::vector<std::string> split = StringUtil::split(input, '\n');

    std::string operations = split.back();

    const char* str = operations.c_str();
    size_t offset   = 0;
    while(str != nullptr) {
        const char* end = strpbrk(str + 1, "+*");
        size_t len      = end != nullptr ? (end - str) - 1 : strlen(str);

        const char& operation = *str;
        uint64_t out          = (operation == '*' ? 1 : 0);

        for(size_t row = 0; row <= len; row++) {
            uint64_t num = 0;
            for(size_t col = 0; col < split.size() - 1; col++) {
                if(split[col].size() <= row + offset) {
                    break;
                }

                const char& c = split[col][row + offset];
                if(!isdigit(c)) {
                    continue;
                }

                num *= 10;
                num += c - '0';
            }

            if(num == 0) {
                continue;
            }

            switch(operation) {
            case '+': out += num; break;
            case '*': out *= num; break;
            }
        }

        bSolution += out;

        str = end;
        offset += len + 1;
    }
}

void Day6::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}