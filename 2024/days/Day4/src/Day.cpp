#include <DayInput.hpp>
#include <Day.hpp>
#include <cstring>
#include <spdlog/spdlog.h>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

#define SEQUENCE "XMAS"

// must be in the sequence var
char nextInSequence(char c) {
    char temp[2];
    temp[0] = c;
    temp[1] = '\0';

    const char* out = strstr(SEQUENCE, temp);
    if(out == NULL) return '\0';
    else return *(out + 1);
}

bool isOutOfRange(const std::vector<std::string>& grid, long x, long y) {
    return x < 0 || y < 0 || x >= grid[0].size() || y >= grid.size();
}


enum Direction {
    NONE = 0,
    UP = 1 << 0,
    DOWN = 1 << 1,
    LEFT = 1 << 2,
    RIGHT = 1 << 3
};

// starting x, y of the sequence, returns a vector as you may have multiple xmas' branched out from a start
size_t get_sequence(const std::vector<std::string>& grid, long x, long y, size_t direction = Direction::NONE) {
    const char& startChar = grid[y][x];
    const char& nextChar = nextInSequence(startChar);

    if(startChar == 'S') {
        return 1;
    }

    if(direction == NONE) {
        size_t out = 0;
        for(long i = 0; i < 9; i++) {
            long nextX = x + ((i % 3) - 1), nextY = y + ((i / 3) - 1);
            
            if(!isOutOfRange(grid, nextX, nextY) && grid[nextY][nextX] == nextChar) {
                size_t dir = 0;
                if(nextX < x) dir |= Direction::LEFT;
                else if(nextX > x) dir |= Direction::RIGHT;

                if(nextY < y) dir |= Direction::UP;
                else if(nextY > y) dir |= Direction::DOWN;

                out += get_sequence(grid, nextX, nextY, dir);
            }
        }

        return out;
    }
    
    long nextX = x, nextY = y;
    if(direction & DOWN) nextY++;
    else if(direction & UP) nextY--;

    if(direction & RIGHT) nextX++;
    else if(direction & LEFT) nextX--;

    if(!isOutOfRange(grid, nextX, nextY) && grid[nextY][nextX] == nextChar) {
        return get_sequence(grid, nextX, nextY, direction);
    }

    return 0;
}

size_t aSolution = 0;
void Day::partA() {
    std::vector<std::string> grid = input.getSplitText("\n");

    for(long y = 0; y < grid.size(); y++) {
        for(long x = 0; x < grid[0].size(); x++) {
            if(grid[y][x] == 'X') {
                aSolution += get_sequence(grid, x, y);
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
                if(
                    grid[y + 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'S' &&
                    grid[y - 1][x - 1] == 'M' && grid[y - 1][x + 1] == 'S'
                ) {
                    bSolution++;
                }
                else if(
                    grid[y + 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'M' &&
                    grid[y - 1][x - 1] == 'S' && grid[y - 1][x + 1] == 'M'
                ) {
                    bSolution++;
                }
                else if(
                    grid[y + 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'M' &&
                    grid[y - 1][x - 1] == 'S' && grid[y - 1][x + 1] == 'S'
                ) {
                    bSolution++;
                }
                else if(
                    grid[y + 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'S' &&
                    grid[y - 1][x - 1] == 'M' && grid[y - 1][x + 1] == 'M'
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