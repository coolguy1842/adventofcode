#include <Days/Day04.hpp>
#include <Input/Day04.hpp>
#include <Util/StringUtil.hpp>
#include <cstring>

uint64_t checkBoxes(char* grid, size_t gridSize, int64_t width, bool shouldRemove) {
    uint64_t out            = 0;
    const int64_t offsets[] = {
        -(width + 1), -width, (-width) + 1,
        -1, 1,
        width - 1, width, width + 1
    };

    for(int64_t i = 0; i < gridSize; i++) {
        if(grid[i] == '@') {
            uint8_t rolls = 0;
            for(const int64_t& off : offsets) {
                int64_t neighbourIdx = i + off;
                if(
                    neighbourIdx >= 0 && neighbourIdx < gridSize &&
                    (grid[neighbourIdx] == '@' || (!shouldRemove && grid[neighbourIdx] == 'x')) &&
                    ++rolls >= 4
                ) {
                    goto skip;
                }
            }

            grid[i] = 'x';
            out++;
        }

    skip:
    }

    return out;
}

void Day4::partA() {
    std::string grid = input;
    // newlines make a nice wrapper for neighbour checking
    const int64_t width = (strchrnul(grid.c_str(), '\n') - grid.c_str()) + 1;

    aSolution = checkBoxes(grid.data(), input.size(), width, false);
}

void Day4::partB() {
    std::string grid    = input;
    const int64_t width = (strchrnul(grid.c_str(), '\n') - grid.c_str()) + 1;

    for(uint64_t prevSolution = !bSolution; prevSolution != bSolution;) {
        prevSolution = bSolution;
        bSolution += checkBoxes(grid.data(), input.size(), width, true);
    }
}

void Day4::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}