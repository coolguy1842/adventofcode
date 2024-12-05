#include <DayInput.hpp>
#include <Day.hpp>
#include <cstring>
#include <spdlog/spdlog.h>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

size_t aSolution = 0;
void Day::partA() {
    std::string& str = input.text;
    long width = (strstr(str.c_str(), "\n") - str.c_str());

    for(long i = 0; i < str.size(); i++) {
        if(str[i] != 'X') {
            continue;
        }

        for(long j = 0; j < 9; j++) {    
            if(j == 4) {
                continue;
            }

            long dX = (j % 3) - 1, dY = ((j / 3) - 1) * (width + 1);
            long endPos = i + (dX * 3) + (dY * 3);
            
            if(
                (endPos >= 0 || endPos < str.size()) &&
                str[i +  dX      +  dY     ] == 'M' &&
                str[i + (dX * 2) + (dY * 2)] == 'A' &&
                str[i + (dX * 3) + (dY * 3)] == 'S'
            ) {
                aSolution++;
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