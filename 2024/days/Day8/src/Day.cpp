#include <DayInput.hpp>
#include <Day.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Position {
    size_t x, y;

    inline std::size_t operator()(const Position& c) const {
        return (c.x << 32) + c.y;
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

inline void addPosition(std::unordered_set<Position, Position>& antinodes, const size_t& gridWidth, const size_t& gridHeight, const Position& newPos) {
    if(newPos.x >= gridWidth) return;
    else if(newPos.y >= gridHeight) return;

    antinodes.emplace(newPos);
}

void printGrid(const std::vector<std::string>& grid, const std::unordered_set<Position, Position>& antinodes, const size_t& width, const size_t& height, const bool& showAntiOverAntenna) {
    for(size_t y = 0; y < height; y++) {
        for(size_t x = 0; x < width; x++) {
            bool isAntinode = antinodes.contains(Position(x, y));
            bool isAntenna = grid[y][x] != '.';

            if(isAntinode && isAntenna && showAntiOverAntenna) {
                printf("#");
            }
            else if(isAntinode) {
                printf("#");
            }
            else {
                printf("%c", grid[y][x]);
            }
        }

        printf("\n");
    }
}

size_t aSolution = 0;
void Day::partA() {
    const std::vector<std::string> grid = input.getSplitText("\n");
    std::unordered_map<char, std::vector<Position>> antenna;
    std::unordered_set<Position, Position> antinodes;

    size_t gridWidth = grid[0].size(), gridHeight = grid.size();
    for(size_t y = 0; y < gridHeight; y++) {
        for(size_t x = 0; x < gridWidth; x++) {
            if(grid[y][x] != '.') {
                antenna[grid[y][x]].push_back({ x, y });
            }
        }
    }

    for(const auto& frequency : antenna) {
        for(size_t i = 0; i <= frequency.second.size() / 2; i++) {
            const Position& a = frequency.second[i];
            for(size_t j = 0; j <= frequency.second.size() / 2; j++) {
                const Position& b = frequency.second[frequency.second.size() - (1 + j)];

                size_t xDiff = (long)a.x - (long)b.x, yDiff = (long)a.y - (long)b.y;
                if(xDiff == 0 && yDiff == 0) {
                    continue;
                }

                addPosition(antinodes, gridWidth, gridHeight, Position(a.x + xDiff, a.y + yDiff));
                addPosition(antinodes, gridWidth, gridHeight, Position(b.x - xDiff, b.y - yDiff));
            }
        }
    }

    for(const Position& pos : antinodes) {
        aSolution++;
    }
}

size_t bSolution = 0;
void Day::partB() {
    const std::vector<std::string> grid = input.getSplitText("\n");
    std::unordered_map<char, std::vector<Position>> antenna;
    std::unordered_set<Position, Position> antinodes;

    size_t gridWidth = grid[0].size(), gridHeight = grid.size();
    for(size_t y = 0; y < gridHeight; y++) {
        for(size_t x = 0; x < gridWidth; x++) {
            if(grid[y][x] != '.') {
                antenna[grid[y][x]].push_back({ x, y });
            }
        }
    }

    for(const auto& frequency : antenna) {
        for(size_t i = 0; i <= frequency.second.size() / 2; i++) {
            const Position& a = frequency.second[i];
            for(size_t j = 0; j <= frequency.second.size() / 2; j++) {
                const Position& b = frequency.second[frequency.second.size() - (1 + j)];

                size_t xDiff = (long)a.x - (long)b.x, yDiff = (long)a.y - (long)b.y;
                if(xDiff == 0 && yDiff == 0) {
                    continue;
                }

                Position pos = { a.x, a.y };
                addPosition(antinodes, gridWidth, gridHeight, Position(pos.x, pos.y));
                while(pos.x < gridWidth && pos.y < gridWidth) {
                    addPosition(antinodes, gridWidth, gridHeight, Position(pos.x += xDiff, pos.y += yDiff));
                }

                pos = { b.x, b.y };
                addPosition(antinodes, gridWidth, gridHeight, Position(pos.x, pos.y));
                while(pos.x < gridWidth && pos.y < gridWidth) {
                    addPosition(antinodes, gridWidth, gridHeight, Position(pos.x -= xDiff, pos.y -= yDiff));
                }
            }
        }
    }

    for(const Position& pos : antinodes) {
        bSolution++;
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}