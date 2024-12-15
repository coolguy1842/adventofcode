#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdint>
#include <spdlog/spdlog.h>
#include <string>
#include <utility>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

enum GridObject {
    NONE = '.',
    WALL = '#',
    GUARD = '@',
    BLOCK = 'O'
};

enum Direction {
    UP = '^',
    LEFT = '<',
    DOWN = 'v',
    RIGHT = '>'
};


struct Position {
    uint64_t x, y;
};

struct Guard {
    Position pos;
};

void printGrid(const std::vector<std::string>& grid) {
    for(const std::string& line : grid) {
        spdlog::info("{}", line);
    }

    spdlog::info("");
}

void moveGuard(std::vector<std::string>& grid, Guard& guard, int64_t dX, int64_t dY) {
    Position pos = guard.pos;

    bool foundPos = false;
    while(!foundPos) {
        pos.y += dY;
        pos.x += dX;

        const char& curChar = grid[pos.y][pos.x];
        switch(curChar) {
        case WALL: return;
        case NONE: foundPos = true; break;
        default: break;
        }
    }

    while(pos.x != guard.pos.x || pos.y != guard.pos.y) {
        std::swap(grid[pos.y][pos.x], grid[pos.y - dY][pos.x - dX]);
        
        pos.y -= dY;
        pos.x -= dX;
    }

    guard.pos.x += dX;
    guard.pos.y += dY;
}

uint64_t aSolution = 0;
void Day::partA() {
    const std::vector<std::string>& split = input.getSplitText("\n");
    
    std::vector<std::string> grid;
    std::string directions;

    Guard guard;

    bool doDirections = false;
    for(size_t i = 0; i < split.size(); i++) {
        if(split[i].size() == 0) {
            doDirections = true;
        }

        if(doDirections) {
            directions += split[i];
        }
        else {
            grid.push_back(split[i]);
        }
    }

    for(size_t y = 0; y < grid.size(); y++) {
        for(size_t x = 0; x < grid[0].size(); x++) {
            if(grid[y][x] == GUARD) {
                guard.pos.y = y;
                guard.pos.x = x;

                goto foundGuard;
            }
        }
    }

    foundGuard:
    for(const char& c : directions) {
        switch(c) {
        case UP   : moveGuard(grid, guard,  0,  -1); break;
        case LEFT : moveGuard(grid, guard, -1,  0); break;
        case DOWN : moveGuard(grid, guard,  0, 1); break;
        case RIGHT: moveGuard(grid, guard,  1,  0); break;
        default: break;
        }
    }

    for(size_t y = 0; y < grid.size(); y++) {
        for(size_t x = 0; x < grid[0].size(); x++) {
            if(grid[y][x] == BLOCK) {
                aSolution += (y * 100) + x;
            }
        }
    }
}

void Day::partB() {

}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution); 
}