#include <DayInput.hpp>
#include <Day.hpp>
#include <cstring>
#include <spdlog/spdlog.h>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

size_t aSolution = 0;
void Day::partA() {
    const size_t& strSize = input.text.size();
    
    const char *strPtr = input.text.c_str(), *ptr = strPtr - 1;
    long width = strstr(strPtr, "\n") - strPtr;
    
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

size_t bSolution = 0;
void Day::partB() {
    std::vector<std::string> grid = input.getSplitText("\n");

    for(long y = 1; y < grid.size() - 1; y++) {
        for(long x = 1; x < grid[0].size() - 1; x++) {
            if(grid[y][x] == 'A') {
                char &topLeft = grid[y - 1][x - 1], topRight = grid[y - 1][x + 1];
                char &bottomLeft = grid[y + 1][x - 1], bottomRight = grid[y + 1][x + 1];

                if(
                    topLeft != bottomRight &&
                    (topLeft == 'M' || topLeft == 'S') && (bottomRight == 'M' || bottomRight == 'S') &&
                    ((topLeft == topRight && bottomLeft == bottomRight) || (topLeft == bottomLeft && topRight == bottomRight))
                ) {
                    bSolution++;
                }
            }
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}