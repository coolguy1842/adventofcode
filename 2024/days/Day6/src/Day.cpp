#include <DayInput.hpp>
#include <Day.hpp>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>
#include <spdlog/spdlog.h>
#include <string>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Position {
    size_t x, y;
};

enum Direction {
    NONE  = 0,
    UP    = 1 << 0,
    RIGHT = 1 << 1,
    DOWN  = 1 << 2,
    LEFT  = 1 << 3
};

struct Guard {
    Position pos;
    Direction dir = UP;
};

enum GridType {
    EMPTY,
    BLOCK,
    BORDER
};

struct GridPosition {
    GridType type;
    long visited;
};

inline Direction rotateDir(const Direction& dir) {
    if(dir == Direction::LEFT) {
        return Direction::UP;
    }

    return (Direction)(dir << 1);
}

struct Grid {
    size_t width, height;
    GridPosition** data;

    Guard guard;


    void resetVisited() {
        for(size_t y = 0; y <= height + 1; y++) {
            for(size_t x = 0; x <= width + 1; x++) {
                data[y][x].visited = NONE;
            }
        }
    }

    bool countVisited() {
        for(size_t y = 0; y <= height + 1; y++) {
            for(size_t x = 0; x <= width + 1; x++) {
                data[y][x].visited = NONE;
            }
        }
    }


    Grid(const std::string& input) {
        const char* strPtr = input.c_str();
        width = strpbrk(strPtr, "\n") - strPtr;
        height = input.size() / width;
        
        data = (GridPosition**)calloc(height + 2, sizeof(GridPosition*));
        
        for(size_t y = 0; y <= height + 1; y++) {
            data[y] = (GridPosition*)calloc(width + 2, sizeof(GridPosition));
            for(size_t x = 0; x <= width + 1; x++) {
                data[y][x].type = GridType::BORDER;
                data[y][x].visited = NONE;
            }
        }

        size_t x = 1, y = 1;
        for(size_t i = 0; i < input.size(); i++) {
            switch(strPtr[i]) {
            case '#': data[y][x++].type = GridType::BLOCK; break;
            case '^': guard.pos = { x, y };
            case '.': data[y][x++].type = GridType::EMPTY; break;
            case '\n':
                x = 1;
                y++;

                break;
            }
        }
    }

    ~Grid() {
        free(data);
    }


    void stepGuard() {
        long dX = 0, dY = 0;
        
        switch(guard.dir) {
        case UP   : dY = -1; break;
        case RIGHT: dX =  1; break;
        case DOWN : dY =  1; break;
        case LEFT : dX = -1; break;
        default: break;
        }

        if(data[guard.pos.y + dY][guard.pos.x + dX].type == GridType::BLOCK) {
            guard.dir = rotateDir(guard.dir);

            return;
        }

        data[guard.pos.y][guard.pos.x].visited |= guard.dir;

        guard.pos.y += dY;
        guard.pos.x += dX;
    }
};

size_t aSolution = 0;
void Day::partA() {
    Grid grid(input.text);

    while(grid.data[grid.guard.pos.y][grid.guard.pos.x].type != BORDER) {
        grid.stepGuard();
    }

    for(size_t y = 1; y <= grid.height; y++) {
        for(size_t x = 1; x <= grid.width; x++) {
            if(grid.data[y][x].visited != NONE) {
                aSolution++;
            }
        }
    }
}

size_t bSolution = 0;
void Day::partB() {
    Grid grid(input.text);
    Position guardPos = grid.guard.pos;

    // get main path
    while(grid.data[grid.guard.pos.y][grid.guard.pos.x].type != BORDER) {
        grid.stepGuard();
    }

    std::list<Position> possibleBlocks;
    for(size_t y = 1; y <= grid.height; y++) {
        for(size_t x = 1; x <= grid.width; x++) {
            if(grid.data[y][x].visited == NONE || (grid.guard.pos.x == x && grid.guard.pos.y == y)) {
                continue;
            }

            possibleBlocks.push_back(Position(x, y));
        }
    }

    for(const Position& pos : possibleBlocks) {
        GridPosition& block = grid.data[pos.y][pos.x];

        grid.resetVisited();
        grid.guard.pos.x = guardPos.x;
        grid.guard.pos.y = guardPos.y;
        grid.guard.dir = UP;

        GridType prevType = block.type;
        block.type = BLOCK;

        while(grid.data[grid.guard.pos.y][grid.guard.pos.x].type != BORDER) {
            if(grid.data[grid.guard.pos.y][grid.guard.pos.x].visited & grid.guard.dir) {
                bSolution++;
                break;    
            }

            grid.stepGuard();
        }

        block.type = prevType;
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}