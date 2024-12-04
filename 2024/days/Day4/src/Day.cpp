#include <DayInput.hpp>
#include <Day.hpp>
#include <cstring>
#include <spdlog/spdlog.h>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

bool isOutOfRange(const std::vector<std::string>& grid, const long& x, const long& y) {
    return x < 0 || y < 0 || x >= grid[0].size() || y >= grid.size();
}

size_t aSolution = 0;
void Day::partA() {
    std::vector<std::string> grid = input.getSplitText("\n");

    for(long i = 0; i < grid.size(); i++) {
        for(long j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] != 'X') {
                continue;
            }

            for(long k = 0; k < 9; k++) {
                long dX = (k % 3) - 1, dY = (k / 3) - 1;
                
                if( 
                    k != 4 &&
                    !isOutOfRange(grid, j + (dX * 3), i + (dY * 3)) &&
                    grid[i + (dY * 1)][j + (dX * 1)] == 'M' &&
                    grid[i + (dY * 2)][j + (dX * 2)] == 'A' &&
                    grid[i + (dY * 3)][j + (dX * 3)] == 'S'
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