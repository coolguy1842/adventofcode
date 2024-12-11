#include <DayInput.hpp>
#include <Day.hpp>
#include <deque>
#include <list>
#include <map>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <utility>
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


    bool operator<(const Position& other) const {
        return x * y < other.x * other.y;
    }

    bool operator>(const Position& other) const {
        return x > other.x && y > other.y;
    }
};

typedef std::vector<std::string> TGrid;
typedef std::map<Position, std::vector<Position>> TTrailHeads;

std::vector<Position> directions = { Position(-1, 0), Position(1, 0), Position(0, -1), Position(0, 1) };
std::vector<Position> getNeighbours(const TGrid& grid, const Position& pos) {
    const char& c = grid[pos.y][pos.x];
    if(c == '9') {
        return {};
    }

    std::vector<Position> out;
    for(const Position& dir : directions) {
        Position nextPos = Position(pos.x - dir.x, pos.y - dir.y);
        if(nextPos.x < 0 || nextPos.x >= grid[0].size() || nextPos.y < 0 || nextPos.y >= grid.size()) {
            continue;
        }

        const char& next = grid[nextPos.y][nextPos.x];
        if(next == c + 1) {
            out.push_back(Position(nextPos.x, nextPos.y));
        }
    }

    return out;
}

size_t getPaths(const TGrid& grid, TTrailHeads& trailHeadsScore, const Position& startPos, std::vector<Position> trailHeads) {
    Position pos = startPos;

    while(true) {
        for(size_t y = 0; y < grid.size(); y++) {
            for(size_t x = 0; x < grid[0].size(); x++) {
                const char& c = grid[y][x];
                
                if(x == pos.x && y == pos.y) {
                    if(c == '9') {
                        printf("!");
                    }
                    else {
                        printf("*");
                    }
                }
                else {
                    printf("%c", c);
                }
            }

            printf("\n");
        }

        printf("\n");

        if(grid[pos.y][pos.x] == '9') {
            break;
        }

        std::vector<Position> neighbours = getNeighbours(grid, pos);
        
        if(neighbours.size() > 1) {
            trailHeads.push_back(pos);
            size_t out = 0;

            for(const Position& neighbour : neighbours) {
                // if(grid[neighbour.y][neighbour.x] == '9') {
                //     out++;
                // }
                // else {
                    out += getPaths(grid, trailHeadsScore, neighbour, trailHeads);
                // }
            }

            return out;
        }
        else if(neighbours.size() == 0) {
            return 0;
        }

        pos = neighbours[0];
    }

    for(const Position& trailHead : trailHeads) {
        trailHeadsScore[trailHead].push_back(pos);
    }

    return 1;
}

size_t aSolution = 0;
void Day::partA() {
    TGrid grid = input.getSplitText("\n");
    TTrailHeads trailHeads;

    std::vector<Position> startPositions;
    
    for(size_t y = 0; y < grid.size(); y++) {
        for(size_t x = 0; x < grid[0].size(); x++) {
            const char& c = grid[y][x];
            printf("%c", c);

            if(c == '0') {
                startPositions.push_back(Position(x, y));
            }
        }

        printf("\n");
    }

    spdlog::info("Positions: {}", startPositions.size());
    for(Position& pos : startPositions) {
        getPaths(grid, trailHeads, pos, {});
    }

    for(const auto& pair : trailHeads) {
        spdlog::info("trailhead: {}, score: {}", grid[pair.first.y][pair.first.x], pair.second.size());
        aSolution += pair.second.size();
    }
}

void Day::partB() {

}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
}