#include <DayInput.hpp>
#include <Day.hpp>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <limits>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

enum GridType {
    EMPTY = '.',
    WALL = '#',
    START = 'S',
    END = 'E'
};

struct GridObject {
    GridType type;
    uint64_t minScore;
};

struct Node {
    uint64_t score;
    uint64_t position;

    std::vector<uint64_t> path;

    auto operator<=>(const Node& other) const { return score <=> other.score; }
};

void printPath(GridObject* grid, const uint64_t& width, const uint64_t& height, const uint64_t& highlight) {
    for(uint64_t i = 0; i < width * height; i++) {
        if(i % width == 0) {
            printf("\n");
        }

        if(i == highlight) {
            printf("*");
            continue;
        }

        printf("%c", grid[i].type);
    }

    printf("\n");
}

std::vector<uint64_t> findPath(GridObject* grid, const uint64_t& width, const uint64_t& height, const uint64_t& start, const uint64_t& end) {
    const uint64_t directionsNum = 4;
    const uint64_t directions[directionsNum] = { -1LU, -width, 1, width };

    std::vector<uint64_t> path = { start };
    uint64_t pos = start, prevPos = start;
    
    while(pos != end) {
        for(const uint64_t& dir : directions) {
            const uint64_t newPos = pos + dir;
            if(newPos == prevPos || grid[newPos].type == WALL) {
                continue;
            }

            prevPos = pos;
            pos = newPos;
            break;
        }

        path.push_back(pos);
    }

    return path;
}

GridObject* getGrid(const std::string& input, uint64_t& width, uint64_t& height, uint64_t& start, uint64_t& end) {
    const char* strPtr = input.c_str();

    width = strpbrk(strPtr, "\n") - strPtr, height = input.size() / width;
    GridObject* grid = (GridObject*)calloc(width * height, sizeof(GridObject));

    uint64_t i = 0;
    for(const char& c : input) {
        switch (c) {
        case START: start = i; break;
        case END: end = i; break;
        case '\n': continue;
        default: break;
        }

        grid[i++] = { (GridType)c, std::numeric_limits<uint64_t>::max() };
    }

    return grid;
}

uint64_t aSolution = 0;
void Day::partA() {
    uint64_t width, height, start, end;
    GridObject* grid = getGrid(input.text, width, height, start, end);
    
    const std::vector<uint64_t> mainPath = findPath(grid, width, height, start, end);
    const uint64_t directions[4] = { -width, 1, width, -1LU }, &pathSize = mainPath.size();

    for(auto it = mainPath.begin(); it != mainPath.end(); it++) {
        const uint64_t score = std::distance(mainPath.begin(), it);

        for(const uint64_t& direction : directions) {
            const uint64_t pos = *it + (direction * 2);
            if(grid[*it + direction].type != WALL) {
                continue;
            }
            else if(pos >= width * height) {
                continue;
            }

            const auto hackedIt = std::find(mainPath.begin(), mainPath.end(), pos);
            if(hackedIt == mainPath.end()) {
                continue;
            }

            const uint64_t totalScore = score + std::distance(hackedIt, mainPath.end()) + 2;
            const uint64_t saved = pathSize - totalScore;

            if(totalScore >= pathSize || saved < 100) {
                continue;
            }

            aSolution++;
        }
    }

    free(grid);
}

uint64_t bSolution = 0;
void Day::partB() {
    uint64_t width, height, start, end;
    GridObject* grid = getGrid(input.text, width, height, start, end);
    
    const std::vector<uint64_t> mainPath = findPath(grid, width, height, start, end);
    const uint64_t directions[4] = { -width, 1, width, -1LU }, &pathSize = mainPath.size();

    free(grid);
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}