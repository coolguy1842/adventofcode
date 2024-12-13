#include <DayInput.hpp>
#include <Day.hpp>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Position {
    uint64_t x, y;

    inline std::size_t operator()(const Position& c) const {
        return (c.x << 32) + c.y;
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

struct PlotInfo {
    uint64_t area;
    uint64_t perimeter;
};

PlotInfo getPlotInfo(const std::vector<std::string>& grid, bool** visited, Position pos) {
    constexpr static Position directions[] = { Position(-1, 0), Position(1, 0), Position(0, -1), Position(0, 1)  };
    PlotInfo info = { 0, 0 };

    visited[pos.y][pos.x] = true;
    const char& gardenChar = grid[pos.y][pos.x];

    for(Position dir : directions) {
        Position neighbourPos = Position(pos.x + dir.x, pos.y + dir.y);
        if(neighbourPos.x >= grid[0].size() || neighbourPos.y >= grid.size()) {
            info.perimeter++;

            continue;
        }

        const char& neighbourChar = grid[neighbourPos.y][neighbourPos.x];
        const bool& isVisited = visited[neighbourPos.y][neighbourPos.x];

        if(gardenChar == neighbourChar) {
            if(isVisited) {
                continue;
            }
            
            info.area++;

            visited[neighbourPos.y][neighbourPos.x] = true;
            PlotInfo neighbourInfo = getPlotInfo(grid, visited, neighbourPos);

            info.area += neighbourInfo.area;
            info.perimeter += neighbourInfo.perimeter;

            continue;
        }

        info.perimeter++;
    }

    return info;
}

size_t aSolution = 0;
void Day::partA() {
    const std::vector<std::string>& grid = input.getSplitText("\n");
    const size_t &width = grid[0].size(), &height = grid.size();

    bool** visited = new bool*[height];
    for(size_t i = 0; i < height; i++) {
        visited[i] = new bool[width];
        memset(visited[i], false, width * sizeof(bool));
    }

    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            if(visited[i][j]) {
                continue;
            }

            PlotInfo info = getPlotInfo(grid, visited, Position(j, i));
            info.area += 1;
            aSolution += info.area * info.perimeter;
        }
    }

    for(int i = 0; i < height; ++i) {
        delete[] visited[i];
    }

    delete[] visited;
}


enum Side {
    NONE   = 0,
    TOP    = (1 << 0),
    LEFT   = (1 << 1),
    BOTTOM = (1 << 2),
    RIGHT  = (1 << 3)
};

struct PlotInfoB {
    uint64_t area;
    uint64_t sides;
};

PlotInfoB getPlotInfoB(const std::vector<std::string>& grid, bool** visited, Position pos, std::unordered_map<Position, uint64_t, Position>& sides) {
    constexpr static Position directions[] = { Position(0, -1), Position(-1, 0), Position(0, 1), Position(1, 0) };
    PlotInfoB info = { 0, 0 };

    visited[pos.y][pos.x] = true;
    const char& gardenChar = grid[pos.y][pos.x];
    
    sides[pos] = NONE;
    size_t edges = 0;

    for(size_t i = 0; i < 4; i++) {
        const Position& dir = directions[i];

        Position neighbourPos = Position(pos.x + dir.x, pos.y + dir.y);
        if(neighbourPos.x >= grid[0].size() || neighbourPos.y >= grid.size()) {
            goto assignSide;
        }

        {
            const char& neighbourChar = grid[neighbourPos.y][neighbourPos.x];
            const bool& isVisited = visited[neighbourPos.y][neighbourPos.x];

            if(gardenChar == neighbourChar) {
                if(isVisited) {
                    continue;
                }
                
                info.area++;

                visited[neighbourPos.y][neighbourPos.x] = true;
                PlotInfoB neighbourInfo = getPlotInfoB(grid, visited, neighbourPos, sides);

                info.area += neighbourInfo.area;
                info.sides += neighbourInfo.sides;

                continue;
            }
        }

        assignSide:
        if(sides.find(pos) == sides.end()) {
            sides[pos] = (1 << i);
        }
        else {
            sides[pos] |= (1 << i);
        }

        skip:
    }

    return info;
}


bool doSide(const std::vector<std::string>& grid, std::unordered_map<Position, uint64_t, Position>& sides, const Position& pos, const Side& checkSide) {
    auto it = sides.find(pos);
    if(it == sides.end()) {
        return false;
    }

    if(!(it->second & checkSide)) {
        if(it->second == NONE) {
            sides.erase(it);
        }
        
        return false;
    }

    uint64_t minX = pos.x, maxX = pos.x, minY = pos.y, maxY = pos.y;
    if(checkSide == TOP || checkSide == BOTTOM) {
        // get the left most point
        while(true) {
            if(minX == 0) {
                break;
            }

            auto it = sides.find(Position(minX - 1, pos.y));
            if(it == sides.end() || !(it->second & checkSide)) {
                break;
            }

            minX--;
        }

        // get the right most point
        while(true) {
            if(maxX + 1 >= grid[0].size()) {
                break;
            }
            
            auto it = sides.find(Position(maxX + 1, pos.y));
            if(it == sides.end() || !(it->second & checkSide)) {
                break;
            }

            maxX++;
        }
    }
    else if(checkSide == LEFT || checkSide == RIGHT) {
        // get the top most point
        while(true) {
            if(minY == 0) {
                break;
            }

            auto it = sides.find(Position(pos.x, minY - 1));
            if(it == sides.end() || !(it->second & checkSide)) {
                break;
            }

            minY--;
        }

        // get the right most point
        while(true) {
            if(maxY + 1 >= grid.size()) {
                break;
            }

            auto it = sides.find(Position(pos.x, maxY + 1));
            if(it == sides.end() || !(it->second & checkSide)) {
                break;
            }

            maxY++;
        }
    }

    for(uint64_t y = minY; y <= maxY; y++) {
        for(uint64_t x = minX; x <= maxX; x++) {
            Position p = Position(x, y);
            uint64_t& side = sides[p];

            side &= (~checkSide);
        }
    }

    return true;
}


size_t bSolution = 0;
void Day::partB() {
    const std::vector<std::string>& grid = input.getSplitText("\n");
    const size_t &width = grid[0].size(), &height = grid.size();

    bool** visited = new bool*[height];
    for(size_t i = 0; i < height; i++) {
        visited[i] = new bool[width];
        memset(visited[i], false, width * sizeof(bool));
    }

    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            if(visited[i][j] || grid[i][j] == '.') {
                continue;
            }

            std::unordered_map<Position, uint64_t, Position> sides;
            PlotInfoB info = getPlotInfoB(grid, visited, Position(j, i), sides);

            while(sides.size()) {
                auto side = sides.begin();

                info.sides += doSide(grid, sides, side->first, TOP);;
                info.sides += doSide(grid, sides, side->first, LEFT);
                info.sides += doSide(grid, sides, side->first, BOTTOM);
                info.sides += doSide(grid, sides, side->first, RIGHT);
            }

            info.area += 1;
            bSolution += info.area * info.sides;
        }
    }

    for(int i = 0; i < height; ++i) {
        delete[] visited[i];
    }

    delete[] visited;
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}