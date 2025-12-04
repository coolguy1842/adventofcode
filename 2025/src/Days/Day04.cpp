#include <Days/Day04.hpp>
#include <Input/Day04.hpp>
#include <Util/StringUtil.hpp>
#include <cmath>
#include <cstdint>
#include <cstring>

uint64_t removeRolls(char* grid, const int64_t width, const int64_t height, bool first = true) {
    uint64_t out = 0;

    for(int64_t y = 0; y < height; y++) {
        for(int64_t x = 0; x < width; x++) {
            const int64_t i = (y * (width + 1)) + x;
            switch(grid[i]) {
            case '@': {
                int64_t rolls = 0;
                for(int64_t j = 0; j < 9; j++) {
                    if(j == 4) {
                        continue;
                    }

                    int64_t neighbourX = x + (j % 3) - 1;
                    int64_t neighbourY = y + (j / 3) - 1;

                    if(
                        neighbourX < 0 || neighbourX >= width ||
                        neighbourY < 0 || neighbourY >= height
                    ) {
                        continue;
                    }

                    if(grid[(neighbourY * (width + 1)) + neighbourX] == '@') {
                        rolls++;
                    }

                    if(rolls >= 4) {
                        goto skip;
                    }
                }

                out++;
                if(!first) {
                    grid[i] = '.';
                }
            skip:
                break;
            }
            default: break;
            }
        }
    }

    return out;
}

void Day4::partA() {
    char* grid           = strdup(input.c_str());
    const int64_t width  = strchrnul(grid, '\n') - grid;
    const int64_t height = input.size() / width;

    aSolution = removeRolls(grid, width, height);

    free(grid);
}

void Day4::partB() {
    char* grid           = strdup(input.c_str());
    const int64_t width  = strchrnul(grid, '\n') - grid;
    const int64_t height = input.size() / width;

    uint64_t moved = 0;
    do {
        moved = removeRolls(grid, width, height, false);
        bSolution += moved;
    } while(moved);

    free(grid);
}

void Day4::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}