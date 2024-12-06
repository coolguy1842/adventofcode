#include <DayInput.hpp>
#include <Day.hpp>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}
struct Position {
    long x, y;

    inline std::size_t operator()(const Position& p) const {
        return (p.x << 32) + p.y;
    }

    inline bool operator==(const Position& p) const {
        return x == p.x && y == p.y;
    }
};

enum Direction {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

struct Guard {
    Position pos;
    Direction dir;
};

enum GridType {
    EMPTY,
    BLOCK,
    BORDER
};

struct Grid {
    Grid(size_t width, size_t height) : width(width), height(height) {
        data = (GridType**)calloc(height + 2, sizeof(GridType*));
        visited = {};

        for(long y = 0; y <= height + 1; y++) {
            data[y] = (GridType*)calloc(width + 2, sizeof(GridType));
            for(long x = 0; x <= width + 1; x++) {
                data[y][x] = GridType::BORDER;
            }
        }
    }

    Grid(Grid& otherGrid) {
        this->width = otherGrid.width;
        this->height = otherGrid.height;

        this->guard = otherGrid.guard;
        this->visited = otherGrid.visited;

        data = (GridType**)calloc(height + 2, sizeof(GridType*));

        for(long y = 0; y <= height + 1; y++) {
            data[y] = (GridType*)calloc(width + 2, sizeof(GridType));
            memcpy(data[y], otherGrid.data[y], (width + 2) * sizeof(GridType));
        }
    }

    ~Grid() {
        free(data);
    }

    size_t width, height;

    GridType** data;
    std::unordered_map<Position, std::set<Direction>, Position> visited;

    Guard guard;
};

inline Direction rotateDir(const Direction& dir) {
    if(dir == Direction::LEFT) {
        return Direction::UP;
    }

    return (Direction)(dir + 1);
}

void stepGuard(Grid& grid) {
    long dX = 0, dY = 0;
    Position& pos = grid.guard.pos;
    Direction& dir = grid.guard.dir;

    switch(dir) {
    case UP   : dY = -1; break;
    case RIGHT: dX =  1; break;
    case DOWN : dY =  1; break;
    case LEFT : dX = -1; break;
    default: break;
    }

    if(grid.data[pos.y + dY][pos.x + dX] == GridType::BLOCK) {
        dir = rotateDir(dir);

        return;
    }

    grid.visited[Position(pos.x, pos.y)].emplace(dir);

    pos.y += dY;
    pos.x += dX;
}

size_t aSolution = 0;
void Day::partA() {
    const std::vector<std::string>& lines = input.getSplitText("\n");

    Grid grid(lines[0].size(), lines.size());

    for(long y = 1; y <= lines.size(); y++) {
        for(long x = 1; x <= lines[0].size(); x++) {
            switch(lines[y - 1][x - 1]) {
            case '#':
                grid.data[y][x] = GridType::BLOCK;
                break;
            case '^':
                grid.guard.pos = Position(x, y);
                grid.guard.dir = UP;
            default: grid.data[y][x] = GridType::EMPTY; break;
            }
        }
    }

    while(grid.data[grid.guard.pos.y][grid.guard.pos.x] != BORDER) {
        stepGuard(grid);
    }

    for(size_t y = 1; y <= grid.height; y++) {
        for(size_t x = 1; x <= grid.width; x++) {
            if(grid.visited.contains(Position(x, y))) {
                aSolution++;
            }
        }
    }
}

size_t bSolution = 0;
void Day::partB() {
const std::vector<std::string>& lines = input.getSplitText("\n");

    Grid grid(lines[0].size(), lines.size());

    for(long y = 1; y <= lines.size(); y++) {
        for(long x = 1; x <= lines[0].size(); x++) {
            switch(lines[y - 1][x - 1]) {
            case '#':
                grid.data[y][x] = GridType::BLOCK;
                break;
            case '^':
                grid.guard.pos = Position(x, y);
                grid.guard.dir = UP;
            default: grid.data[y][x] = GridType::EMPTY; break;
            }
        }
    }

    Grid mainPathGrid = grid;
    // get main path
    while(mainPathGrid.data[mainPathGrid.guard.pos.y][mainPathGrid.guard.pos.x] != BORDER) {
        stepGuard(mainPathGrid);
    }

    std::vector<Position> possibleBlocks;
    for(size_t y = 1; y <= mainPathGrid.height; y++) {
        for(size_t x = 1; x <= mainPathGrid.width; x++) {
            if((grid.guard.pos.x == x && grid.guard.pos.y == y) || !mainPathGrid.visited.contains(Position(x, y))) {
                continue;
            }

            possibleBlocks.push_back(Position(x, y));
        }
    }

    for(Position& newBlock : possibleBlocks) {
        Grid tmp = grid;
        tmp.data[newBlock.y][newBlock.x] = BLOCK;

        while(tmp.data[tmp.guard.pos.y][tmp.guard.pos.x] != BORDER) {
            if(tmp.visited[Position(tmp.guard.pos.x, tmp.guard.pos.y)].contains(tmp.guard.dir)) {
                bSolution++;
                break;    
            }

            stepGuard(tmp);
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}