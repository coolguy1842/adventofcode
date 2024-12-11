#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdint>
#include <list>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_set>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Position {
    long x, y;

    inline std::size_t operator()(const Position& c) const {
        return (c.x << 32) + c.y;
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

typedef std::vector<std::string> TGrid;

std::vector<Position> directions = { Position(-1, 0), Position(1, 0), Position(0, -1), Position(0, 1) };
std::vector<Position> getNeighbours(const TGrid& grid, const Position& pos) {
    const char nextChar = grid[pos.y][pos.x] + 1;

    std::vector<Position> out;
    for(const Position& dir : directions) {
        Position nextPos = Position(pos.x + dir.x, pos.y + dir.y);
        if(nextPos.x < 0 || nextPos.x >= grid[0].size() || nextPos.y < 0 || nextPos.y >= grid.size()) {
            continue;
        }

        const char& next = grid[nextPos.y][nextPos.x];
        if(next == nextChar) {
            out.push_back(Position(nextPos.x, nextPos.y));
        }
    }

    return out;
}


size_t getPaths(const TGrid& grid, std::unordered_set<Position, Position>& trailHeadScores, Position pos) {
    while(grid[pos.y][pos.x] != '9') {
        std::vector<Position> neighbours = getNeighbours(grid, pos);
        switch(neighbours.size()) {
        case 0: return 0;
        case 1: pos = neighbours[0]; break;
        default:
            size_t out = 0;
            for(const Position& neighbour : neighbours) {
                out += getPaths(grid, trailHeadScores, neighbour);
            }

            return out;
        }
    }

    trailHeadScores.emplace(pos);
    return 1;
}

size_t getPathsB(const TGrid& grid, std::list<Position>& trailHeadScores, Position pos) {
    while(grid[pos.y][pos.x] != '9') {
        std::vector<Position> neighbours = getNeighbours(grid, pos);
        switch(neighbours.size()) {
        case 0: return 0;
        case 1: pos = neighbours[0]; break;
        default:
            size_t out = 0;
            for(const Position& neighbour : neighbours) {
                out += getPathsB(grid, trailHeadScores, neighbour);
            }

            return out;
        }
    }

    trailHeadScores.push_back(pos);
    return 1;
}

size_t aSolution = 0;
void Day::partA() {
    TGrid grid = input.getSplitText("\n");
    
    for(size_t y = 0; y < grid.size(); y++) {
        for(size_t x = 0; x < grid[0].size(); x++) {
            if(grid[y][x] == '0') {
                std::unordered_set<Position, Position> endPositions;
                getPaths(grid, endPositions, Position(x, y));

                aSolution += endPositions.size();
            }
        }
    }
}

uint64_t bSolution = 0;
void Day::partB() {
    TGrid grid = input.getSplitText("\n");
    
    for(size_t y = 0; y < grid.size(); y++) {
        for(size_t x = 0; x < grid[0].size(); x++) {
            if(grid[y][x] == '0') {
                std::list<Position> endPositions;
                getPathsB(grid, endPositions, Position(x, y));

                bSolution += endPositions.size();
            }
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}