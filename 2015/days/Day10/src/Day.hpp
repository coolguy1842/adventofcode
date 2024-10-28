#ifndef __DAY_HPP__
#define __DAY_HPP__

#include "utils/StringUtils.hpp"
#include <IDay.hpp>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>
#include <utils/Range.hpp>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

#define MAX_LEN 4000000

class Day : public AOCUtil::IDay {
private:
    size_t aSolution;
    size_t bSolution;

    size_t sayNumbers(char* numbers, char* out) {
        char* write = out;
        size_t chainLength = 0;

        do {
            chainLength++;
            
            if(*numbers != *(numbers + 1)) {
                size_t numStrLen = AOCUtil::numerictostr(chainLength, write); 
                *((write += numStrLen)++) = *numbers;

                chainLength = 0;
            }
        } while(*++numbers);

        return write - out;
    }

    size_t partFunc(size_t loops) {
        char *out = (char*)malloc(MAX_LEN), *copy = (char*)malloc(MAX_LEN);

        size_t strLen = input.text.size();
        memcpy(out, input.text.c_str(), strLen);

        for(size_t i : AOCUtil::Range(loops)) {
            memcpy(copy, out, strLen);
            strLen = sayNumbers(copy, out);    
        }

        free(out);
        free(copy);

        return strLen;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH) {}

    void partA() {
       aSolution = partFunc(40);
    }

    void partB() {
       bSolution = partFunc(50);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aSolution);
        if(partB) spdlog::info("Part B: {}", bSolution);
    }
};

#endif