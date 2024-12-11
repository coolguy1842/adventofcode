#include <DayInput.hpp>
#include <Day.hpp>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <list>
#include <spdlog/spdlog.h>
#include <string>

Day::Day() : AOCUtil::IDay(dayInput) {}

void getPaths(const char* grid, const size_t& width, const size_t& gridSize, std::list<size_t>& endPositions, size_t pos) {
    if(grid[pos] == '9') {
        endPositions.push_back(pos);
        return;
    }

    // newlines cause + 1 needed
    const int64_t posOffsets[] = { 1, -1, static_cast<int64_t>(width + 1), -static_cast<int64_t>(width + 1) };
    const char nextChar = grid[pos] + 1;

    for(const int64_t& offset : posOffsets) {
        const size_t neighbour = pos + offset;
        // no x wrapping check needed as itll find a new line char code, lucky
        if(neighbour < gridSize && grid[neighbour] == nextChar) {
            getPaths(grid, width, gridSize, endPositions, neighbour);
        }
    }
}

uint64_t partFunc(const std::string& input, const bool& partA) {
    uint64_t out = 0;

    const char* grid = input.c_str();
    const size_t& gridSize = input.size();
    const size_t width = strpbrk(grid, "\n") - grid, height = gridSize / width;

    std::list<size_t> endPositions;
    for(size_t i = 0; i < gridSize; i++) {
        if(grid[i] == '0') {
            getPaths(grid, width, gridSize, endPositions, i);

            if(partA) {
                endPositions.sort();
                endPositions.unique();
            }

            out += endPositions.size();
            endPositions.clear();
        }
    }

    return out;
}

uint64_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text, true); }
void Day::partB() { bSolution = partFunc(input.text, false); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}