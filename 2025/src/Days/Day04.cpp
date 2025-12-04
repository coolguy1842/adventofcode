#include <Days/Day04.hpp>
#include <Input/Day04.hpp>
#include <Util/StringUtil.hpp>
#include <cmath>
#include <cstdint>
#include <cstring>

// true if box
inline bool checkNeighbour(const char* grid, const int64_t neighbourIdx, const int64_t width) {
    return neighbourIdx >= 0 && grid[neighbourIdx] == '@';
}

uint64_t checkBoxes(char* grid, size_t gridSize, int64_t width, bool shouldRemove) {
    uint64_t out            = 0;
    const int64_t offsets[] = {
        -(width + 1), -width, (-width) + 1,
        -1, 1,
        width - 1, width, width + 1
    };

    for(int64_t i = 0; i < input.size(); i++) {
        if(grid[i] == '@') {
            uint8_t rolls = 0;
            for(const int64_t& off : offsets) {
                if(checkNeighbour(grid, i + off, width) && ++rolls >= 4) {
                    goto skip;
                }
            }

            if(shouldRemove) {
                grid[i] = '.';
            }

            out++;
        }

    skip:
    }

    return out;
}

void Day4::partA() {
    const char* grid = input.c_str();
    // newlines make a nice wrapper for neighbour checking
    const int64_t width = (strchrnul(grid, '\n') - grid) + 1;

    aSolution = checkBoxes(const_cast<char*>(grid), input.size(), width, false);
}

void Day4::partB() {
    char* grid          = strdup(input.c_str());
    const int64_t width = (strchrnul(grid, '\n') - grid) + 1;

    for(uint64_t prevSolution = !bSolution; prevSolution != bSolution;) {
        prevSolution = bSolution;
        bSolution += checkBoxes(grid, input.size(), width, true);
    }

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