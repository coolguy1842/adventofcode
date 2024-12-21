#include <DayInput.hpp>
#include <Day.hpp>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

    uint64_t startOffset;
    uint64_t endOffset;
};

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

uint64_t getManhattanDist(const int64_t& a, const int64_t& b, const int64_t& width) {
    return std::abs((b % width) - (a % width)) + std::abs((b / width) - (a / width));
}


uint64_t partFunc(const char* text, const int64_t& minSaved, const int64_t& cheatDistance) {
    uint64_t width, height, start, end, out = 0;
    GridObject* grid = getGrid(text, width, height, start, end);

    const uint64_t gridSize = width * height;

    const std::vector<uint64_t> mainPath = findPath(grid, width, height, start, end);
    const uint64_t directions[4] = { -width, 1, width, -1LU }, &pathSize = mainPath.size();
   
    uint64_t offset = 0;
    for(const uint64_t& pos : mainPath) {
        GridObject& obj = grid[pos];

        obj.endOffset = pathSize - offset;
        obj.startOffset = offset++;
    }

    for(const uint64_t& startPos : mainPath) {
        const uint64_t& startScore = grid[startPos].startOffset;

        for(const uint64_t& endPos : mainPath) {
            const uint64_t distance = getManhattanDist(startPos, endPos, width);
            if(distance > cheatDistance) {
                continue;
            }

            if((int64_t)(pathSize - (startScore + grid[endPos].endOffset + distance)) >= minSaved) {
                out++;
            }
        }
    }

    free(grid);
    return out;
}


uint64_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text.c_str(), 100, 2); }
void Day::partB() { bSolution = partFunc(input.text.c_str(), 100, 20); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}