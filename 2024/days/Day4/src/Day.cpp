#include <DayInput.hpp>
#include <Day.hpp>
#include <cstring>
#include <spdlog/spdlog.h>

// both use these variables so just define in one macro
#define INIT_VARS() \
    const size_t& strSize = input.text.size(); \
    const char *strPtr = input.text.c_str(), *ptr = strPtr - 1; \
    long width = strstr(strPtr, "\n") - strPtr;

Day::Day() : AOCUtil::IDay(dayInput) {}

uint64_t aSolution = 0;
void Day::partA() {
    INIT_VARS()
    
    while((ptr = strstr(ptr + 1, "X"))) {
        size_t i = ptr - strPtr;

        for(long dY = -(width + 1); dY <= (width + 1); dY += (width + 1)) {
            for(long dX = -1; dX <= 1; dX++) {
                size_t endPos = i + (dX * 3) + (dY * 3);
                
                if(
                    // unsigned, so if negative, itll wrap around and be greater than strSize
                    endPos < strSize &&
                    strPtr[i + dX + dY] == 'M' &&
                    strPtr[i + dX + dX + dY + dY] == 'A' &&
                    strPtr[endPos] == 'S'
                ) {
                    aSolution++;
                }
            }
        }
    }
}

uint64_t bSolution = 0;
void Day::partB() {
    INIT_VARS()
    
    while((ptr = strstr(ptr + 1, "A"))) {
        size_t i = ptr - strPtr;
        if(i <= width || i - (strSize - width) <= width) {
            continue;
        }

        const char &topLeft = strPtr[i - width - 2], topRight = strPtr[i -  width];
        const char &bottomLeft = strPtr[i + width], bottomRight = strPtr[i + width + 2];

        if(
            topLeft != bottomRight &&
            (topLeft == 'M' || topLeft == 'S') && (bottomRight == 'M' || bottomRight == 'S') &&
            ((topLeft == topRight && bottomLeft == bottomRight) || (topLeft == bottomLeft && topRight == bottomRight))
        ) {
            bSolution++;
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}