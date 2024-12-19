#include "utils/StringUtils.hpp"
#include <DayInput.hpp>
#include <Day.hpp>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <limits>
#include <optional>
#include <queue>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

// add 1 for range and 2 for padding
const static uint64_t WIDTH = 70 + 3;
const static uint64_t HEIGHT = 70 + 3;

const static uint64_t MAX_BYTES = 1024;

Day::Day() : AOCUtil::IDay(dayInput) {}

enum GridType {
    EMPTY,
    CORRUPTED
};

struct GridObject {
    GridType type = EMPTY;
    uint64_t minScore = UINT64_MAX;
};

struct Node {
    uint64_t position;
    uint64_t score;

    auto operator<=>(const Node& other) const { return score <=> other.score; }
};

std::optional<uint64_t> findPath(GridObject* grid, const uint64_t& width, const uint64_t& start, const uint64_t& end) {
    const int64_t directions[] = { (int64_t)width, 1, -((int64_t)width), -1 };

    std::priority_queue<Node, std::vector<Node>, std::greater<>> queue;
    queue.push({ start, 0 });

    while(!queue.empty()) {
        const Node node = queue.top();
        queue.pop();

        if(node.position == end) {
            return node.score;
        }

        GridObject& curObj = grid[node.position];
        if(node.score > curObj.minScore) {
            continue;
        }

        for(uint64_t i = 0; i < 4; i++) {
            const uint64_t pos = node.position + directions[i];
            const uint64_t nextScore = node.score + 1;

            GridObject& obj = grid[pos];
            if(obj.type == CORRUPTED || nextScore >= obj.minScore) {
                continue;
            }

            obj.minScore = nextScore;
            queue.push({ pos, nextScore });
        }
    }

    return std::nullopt;
}

inline uint64_t addByte(const std::vector<std::string>& split, GridObject* grid, const uint64_t& width, const uint64_t& byte) {
    uint64_t x, y;
    sscanf(split[byte].c_str(), "%lu,%lu", &x, &y);

    const uint64_t coords = (y * width) + x;
    // offset for array padding
    GridObject& obj = grid[coords + width + 1];
    obj.type = CORRUPTED;

    return coords;
};

inline GridObject* createGrid(const std::vector<std::string>& corruptedBytes, const uint64_t& width, const uint64_t& height, const uint64_t& maxBytes) {
    GridObject* grid = (GridObject*)calloc(WIDTH * HEIGHT, sizeof(GridObject));
    for(uint64_t i = 0; i < HEIGHT * WIDTH; i++) {
        // add border around array
        grid[i] = { (GridType)!((i / WIDTH) % (HEIGHT - 1) != 0 && (i % WIDTH) % (WIDTH - 1) != 0), std::numeric_limits<uint64_t>::max() };
    }

    for(uint64_t byte = 0; byte < MAX_BYTES; byte++) {
        addByte(corruptedBytes, grid, WIDTH, byte);
    }

    return grid;
}


std::optional<uint64_t> aSolution;
void Day::partA() {
    GridObject* grid = createGrid(input.getSplitText("\n"), WIDTH, HEIGHT, MAX_BYTES);
    aSolution = findPath(grid, WIDTH, WIDTH + 1, ((HEIGHT * WIDTH) - WIDTH) - 2);

    free(grid);
}

char bSolution[256];
void Day::partB() {
    const std::vector<std::string>& split = input.getSplitText("\n");

    GridObject* grid = createGrid(split, WIDTH, HEIGHT, MAX_BYTES);
    uint64_t cutoffByte = MAX_BYTES + 1;

    while(true) {
        for(size_t i = 0; i < WIDTH * HEIGHT; i++) {
            grid[i].minScore = UINT64_MAX;
        }

        uint64_t coords = addByte(split, grid, WIDTH, cutoffByte++);
        if(!findPath(grid, WIDTH, WIDTH + 1, ((HEIGHT * WIDTH) - WIDTH) - 2).has_value()) {
            int wrote = AOCUtil::numerictostr((coords % WIDTH), bSolution);
            bSolution[wrote++] = ',';
            AOCUtil::numerictostr((coords / WIDTH), bSolution + wrote);

            break;
        }
    }

    free(grid);
}

void Day::printResults(bool partA, bool partB) {
    if(partA) {
        if(aSolution.has_value()) {
            spdlog::info("Part A: {}", aSolution.value());
        }
        else {
            spdlog::info("Part A: Invalid Path.");
        }
    }

    if(partB) spdlog::info("Part B: {}", bSolution);
}