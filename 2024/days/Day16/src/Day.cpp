#include <DayInput.hpp>
#include <Day.hpp>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <optional>
#include <queue>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_set>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

enum Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

enum GridType {
    WALL = '#',
    EMPTY = '.',
    START = 'S',
    END = 'E'
};

struct GridObject {
    GridType type;
    uint64_t minScores[4] = { UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX };
};

struct Node {
    uint64_t position;
    Direction direction;

    uint64_t score;

    auto operator<=>(const Node& other) const { return score <=> other.score; }
};

// dijkstra algorithm
std::optional<uint64_t> findPath(GridObject* grid, const uint64_t& width, const uint64_t& height, const uint64_t& start, const uint64_t& end) {
    const static uint64_t directionOffsets[] = { -width, 1LU, width, -1LU };
    std::priority_queue<Node, std::vector<Node>, std::greater<>> queue;

    queue.push({ start, EAST, 0 });

    while(!queue.empty()) {
        const Node top = queue.top();
        queue.pop();

        if(top.position == end) {
            return top.score;
        }

        for(uint64_t i = NORTH; i <= WEST; i++) {
            const uint64_t offsetPosition = top.position + directionOffsets[i];

            GridObject& obj = grid[offsetPosition];
            uint64_t newScore = top.score + 1 + ((top.direction != i) * 1000);

            if(obj.type == WALL || newScore > obj.minScores[i]) {
                continue;
            }

            obj.minScores[i] = newScore;
            queue.push({ offsetPosition, (Direction)i, newScore });
        }
    }

    return std::nullopt;
}


struct NodeB {
    uint64_t position;
    Direction direction;

    uint64_t score;
    std::vector<uint64_t> path;

    auto operator<=>(const NodeB& other) const { return score <=> other.score; }
};

std::optional<uint64_t> findPathB(GridObject* grid, const uint64_t& width, const uint64_t& height, const uint64_t& start, const uint64_t& end) {
    const static uint64_t directionOffsets[] = { -width, 1LU, width, -1LU };
    std::priority_queue<NodeB, std::vector<NodeB>, std::greater<>> queue;

    queue.push({ start, EAST, 0, { start } });
    std::optional<uint64_t> bestScore;
    std::unordered_set<uint64_t> tiles;

    while(!queue.empty()) {
        NodeB top = queue.top();
        queue.pop();

        top.path.push_back(top.position);
        if(top.position == end) {
            if(bestScore.has_value() && bestScore.value() < top.score) {
                break;
            }

            for(const uint64_t& tile : top.path) {
                tiles.insert(tile);
            }

            bestScore = top.score;
            continue;
        }

        for(uint64_t i = NORTH; i <= WEST; i++) {
            const uint64_t offsetPosition = top.position + directionOffsets[i];
            const uint64_t newScore = top.score + 1 + ((top.direction != i) * 1000);

            GridObject& obj = grid[offsetPosition];

            if(obj.type == WALL || newScore > obj.minScores[i]) {
                continue;
            }

            obj.minScores[i] = newScore;
            queue.push({ offsetPosition, (Direction)i, newScore, top.path });
        }
    }

    if(tiles.size() <= 0) {
        return std::nullopt;
    }

    return tiles.size();
}

std::optional<uint64_t> aSolution;
void Day::partA() {
    const char* strPtr = input.text.c_str();

    const size_t &width = strpbrk(strPtr, "\n") - strPtr, &height = input.text.size() / width;
    GridObject* grid = (GridObject*)calloc(width * height, sizeof(GridObject));
    uint64_t start, end, i = 0;

    for(const char& c : input.text) {
        switch(c) {
        case START: start = i; break;
        case END: end = i; break;
        case '\n': continue;
        default: break;
        }
        
        grid[i++] = { (GridType)c, { UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX } };
    }
    
    aSolution = findPath(grid, width, height, start, end);
}

std::optional<uint64_t> bSolution;
void Day::partB() {
    const char* strPtr = input.text.c_str();

    const size_t &width = strpbrk(strPtr, "\n") - strPtr, &height = input.text.size() / width;
    GridObject* grid = (GridObject*)calloc(width * height, sizeof(GridObject));
    uint64_t start = (width * height) - (width * 2) + 1, end = (width * 2) - 2, i = 0;

    for(const char& c : input.text) {
        if(c == '\n') {
            continue;
        }
        
        grid[i++] = { (GridType)c, { UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX } };
    }
    
    bSolution = findPathB(grid, width, height, start, end);
}

void Day::printResults(bool partA, bool partB) {
    if(partA) {
        if(!aSolution.has_value()) {
            spdlog::info("Part A: No path found.");
        }
        else {
            spdlog::info("Part A: {}", aSolution.value());
        }
    }

    if(partB) {
        if(!bSolution.has_value()) {
            spdlog::info("Part B: No path found.");
        }
        else {
            spdlog::info("Part B: {}", bSolution.value());
        }
    }
}