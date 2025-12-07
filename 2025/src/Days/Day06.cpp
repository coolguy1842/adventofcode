#include <Days/Day06.hpp>
#include <Input/Day06.hpp>
#include <Util/StringUtil.hpp>
#include <cstring>

constexpr size_t lines = 4;

void Day6::partA() {
    const size_t width = (strchrnul(input.c_str(), '\n') - input.c_str()) + 1;

    for(const char* str = input.c_str() + (width * lines); str != NULL;) {
        const char* end  = strpbrk(str + 1, "+*");
        const size_t len = end != nullptr ? (end - str) - 1 : strlen(str);

        const char& operation = *str;
        uint64_t out          = (operation == '*' ? 1 : 0);

        for(size_t num = 0, row = lines; row > 0; row--, num = 0) {
            for(size_t col = 0; col <= len; col++) {
                const char& c = str[(-row * width) + col];
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

        aSolution += out;
        str = end;
    }
}

void Day6::partB() {
    const size_t width = (strchrnul(input.c_str(), '\n') - input.c_str()) + 1;

    for(const char* str = input.c_str() + (width * lines); str != NULL;) {
        const char* end  = strpbrk(str + 1, "+*");
        const size_t len = end != nullptr ? (end - str) - 1 : strlen(str);

        const char& operation = *str;
        uint64_t out          = (operation == '*' ? 1 : 0);

        for(size_t num = 0, row = 0; row <= len; row++, num = 0) {
            for(size_t col = lines; col > 0; col--) {
                const char& c = str[(-col * width) + row];
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