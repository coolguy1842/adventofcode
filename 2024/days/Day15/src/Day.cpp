#include <DayInput.hpp>
#include <Day.hpp>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <string>
#include <utility>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

enum GridObject {
    NONE = '.',
    WALL = '#',
    GUARD = '@',
    BLOCK = 'O',
    BLOCK_HALF_LEFT = '[',
    BLOCK_HALF_RIGHT = ']',
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

void moveGuard(std::vector<std::string>& grid, Position& guard, int64_t dX, int64_t dY) {
    Position pos = guard;

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

    while(pos.x != guard.x || pos.y != guard.y) {
        std::swap(grid[pos.y][pos.x], grid[pos.y - dY][pos.x - dX]);
        
        pos.y -= dY;
        pos.x -= dX;
    }

    guard.x += dX;
    guard.y += dY;
}

uint64_t aSolution = 0;
void Day::partA() {
    const std::vector<std::string>& split = input.getSplitText("\n");
    
    std::vector<std::string> grid;
    std::string directions;

    Position guard;

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
                guard.y = y;
                guard.x = x;

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



bool canMoveObject(std::vector<std::string>& grid, Position position, int64_t dY) {
    Position pos = position;
    uint64_t otherX = 0;

    switch(grid[pos.y][pos.x]) {
    case WALL: return false;
    case NONE: return true;
    case BLOCK_HALF_LEFT: otherX = pos.x + 1; break;
    case BLOCK_HALF_RIGHT: otherX = pos.x - 1; break;
    default:
        switch(grid[pos.y + dY][pos.x]) {
        case WALL: return false;
        case BLOCK_HALF_LEFT: case BLOCK_HALF_RIGHT:
            if(!canMoveObject(grid, Position(pos.x, pos.y + dY), dY)) {
                return false;
            }

            break;
        default: break;
        }
        
        return true;
    }

    const char &left = grid[pos.y + dY][pos.x], &right = grid[pos.y + dY][otherX];
    if(left == WALL || right == WALL) {
        return false;
    }

    if(left == BLOCK_HALF_LEFT || left == BLOCK_HALF_RIGHT || right == BLOCK_HALF_LEFT || right == BLOCK_HALF_RIGHT) {
        if(!canMoveObject(grid, Position(pos.x, pos.y + dY), dY) || !canMoveObject(grid, Position(otherX, pos.y + dY), dY)) {
            return false;
        }
    }
    
    return true;
}

void moveObject(std::vector<std::string>& grid, Position position, int64_t dX, int64_t dY) {
    uint64_t otherX;
    Position pos = position;

    switch(grid[pos.y][pos.x]) {
    case NONE: return;
    case BLOCK_HALF_LEFT: otherX = pos.x + 1; break;
    case BLOCK_HALF_RIGHT: otherX = pos.x - 1; break;
    default:
        if(grid[pos.y + dY][pos.x] != NONE) {
            moveObject(grid, Position(pos.x + dX, pos.y + dY), dX, dY);
        }

        std::swap(grid[pos.y + dY][pos.x + dX], grid[pos.y][pos.x + dX]);
        return;
    }

    moveObject(grid, Position(pos.x, pos.y + dY), dX, dY);
    moveObject(grid, Position(otherX, pos.y + dY), dX, dY);

    std::swap(grid[pos.y][pos.x], grid[pos.y + dY][pos.x + dX]);
    std::swap(grid[pos.y][otherX], grid[pos.y + dY][otherX + dX]);
}


uint64_t bSolution = 0;
void Day::partB() {
    const std::vector<std::string>& split = input.getSplitText("\n");
    
    std::vector<std::string> grid;
    std::string directions;

    Position guard;

    bool doDirections = false;
    for(size_t i = 0; i < split.size(); i++) {
        if(split[i].size() == 0) {
            doDirections = true;
        }

        if(doDirections) {
            directions += split[i];
        }
        else {
            std::string line = "";
            for(const char& c : split[i]) {
                switch(c) {
                case WALL: line += "##"; break;
                case BLOCK: line += "[]"; break;
                case GUARD: line += "@."; break;
                case NONE: line += ".."; break;
                default: break;
                }
            }

            grid.push_back(line);
        }
    }

    for(size_t y = 1; y < grid.size() - 1; y++) {
        for(size_t x = 2; x < grid[0].size() - 2; x++) {
            if(grid[y][x] == GUARD) {
                guard.y = y;
                guard.x = x;

                goto foundGuard;
            }
        }
    }

    foundGuard:
    int64_t step = 0;
    for(const char& c : directions) {
        switch(c) {
        case UP:
            if(canMoveObject(grid, guard, -1)) {
                moveObject(grid, guard, 0, -1);
                guard.y--;
            }

            break;
        case DOWN:
            if(canMoveObject(grid, guard, 1)) {
                moveObject(grid, guard, 0, 1);
                guard.y++;
            }

            break;
        case LEFT: moveGuard(grid, guard, -1, 0); break;
        case RIGHT: moveGuard(grid, guard, 1, 0); break;
        default: break;
        }
    }

    uint64_t width = grid[0].size(), height = grid.size(), halfWidth = (width / 2);
    for(size_t y = 1; y < grid.size() - 1; y++) {
        for(size_t x = 2; x < grid[0].size() - 2; x++) {
            const char& c = grid[y][x];
            switch(c) {
            case BLOCK_HALF_LEFT: {
                bSolution += (y * 100) + x;
                break;
            }
            default: break;
            }
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}