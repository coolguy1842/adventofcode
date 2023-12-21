#ifndef __DAY17_HPP__
#define __DAY17_HPP__

#include <queue>

#include <day.hpp>
#include <stdio.h>

namespace dijkstra {
    
enum direction {
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
    NONE
};


struct position {
    size_t x;
    size_t y;

    dijkstra::direction direction;
    size_t straight;
        
    bool operator==(const position& pos) { return x == pos.x && y == pos.y; }
    bool operator==(const position& pos) const { return x == pos.x && y == pos.y; }
}; 


struct position_hash {
    inline std::size_t operator()(const position& c) const {
        return (c.x << 32) + (c.y << 16) + (c.straight << 8) + c.direction;
    }
};

struct cell {
    struct dijkstra::position position;
    size_t cost = 0;
    
    bool operator>(const cell& other) const { return cost > other.cost; }
};

std::vector<dijkstra::direction> getDirs(dijkstra::direction dir) {
    switch(dir) {
    case dijkstra::direction::NORTH: return { dijkstra::direction::WEST, dijkstra::direction::NORTH, dijkstra::direction::EAST };
    case dijkstra::direction::SOUTH: return { dijkstra::direction::WEST, dijkstra::direction::SOUTH, dijkstra::direction::EAST };
    case dijkstra::direction::EAST: return { dijkstra::direction::NORTH, dijkstra::direction::EAST, dijkstra::direction::SOUTH };
    case dijkstra::direction::WEST: return { dijkstra::direction::NORTH, dijkstra::direction::WEST, dijkstra::direction::SOUTH };
    default: return { dijkstra::direction::WEST, dijkstra::direction::NORTH, dijkstra::direction::EAST, dijkstra::direction::SOUTH };
    }
}

std::vector<cell> getValidNeighbours(const position& pos, std::vector<std::vector<size_t>>& grid) {
    const size_t width = grid[0].size(), height = grid.size();
    std::vector<cell> neighbours;

    const static size_t maxStraight = 3;

    for(dijkstra::direction dir : getDirs(pos.direction)) {
        if(pos.straight >= maxStraight && pos.direction == dir) continue;

        switch (dir) {
        case dijkstra::direction::NORTH: {
            if(pos.y <= 0) continue;
            neighbours.push_back({ {pos.x, pos.y - 1, dijkstra::direction::NORTH, dir == pos.direction ? pos.straight + 1 : 1 }, grid[pos.y - 1][pos.x] });
            
            break;
        }
        case dijkstra::direction::SOUTH: {
            if(pos.y >= height - 1) continue;
            neighbours.push_back({ {pos.x, pos.y + 1, dijkstra::direction::SOUTH, dir == pos.direction ? pos.straight + 1 : 1 }, grid[pos.y + 1][pos.x] });

            break;
        }
        case dijkstra::direction::WEST: {
            if(pos.x <= 0) continue;
            neighbours.push_back({ {pos.x - 1, pos.y, dijkstra::direction::WEST, dir == pos.direction ? pos.straight + 1 : 1 }, grid[pos.y][pos.x - 1] });

            break;            
        }
        case dijkstra::direction::EAST: {
            if(pos.x >= width - 1) continue;
            neighbours.push_back({ {pos.x + 1, pos.y, dijkstra::direction::EAST, dir == pos.direction ? pos.straight + 1 : 1 }, grid[pos.y][pos.x + 1] });

            break;
        }
        default: break;
        }   
    }

    return neighbours;
}

int dijkstraSearch(std::vector<std::vector<size_t>>& grid, const struct position& start, const struct position& dest, int maxScore = __INT_MAX__) {
    std::priority_queue<dijkstra::cell, std::vector<dijkstra::cell>, std::greater<dijkstra::cell>> queue;
    robin_hood::unordered_flat_set<dijkstra::position, dijkstra::position_hash> visited;
    
    queue.push({ start, 0 });
        
    while (!queue.empty()) {
        const dijkstra::cell cur = queue.top();
        queue.pop();

        if(visited.contains(cur.position)) continue;
        if(cur.position == dest) return cur.cost;
        
        visited.emplace(cur.position);

        for (dijkstra::cell& neighbour : getValidNeighbours(cur.position, grid)) {
            neighbour.cost += cur.cost;
            queue.push(neighbour);
        }
    }

    return maxScore;
}

};

class Day17 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    std::vector<std::vector<size_t>> grid = {};

public:
    void loadGrid() {
        grid = std::vector<std::vector<size_t>>(input.size(), std::vector<size_t>());

        for(size_t y = 0; y < input.size(); y++) {
            for(size_t x = 0; x < input[0].size(); x++) {
                grid[y].push_back(this->input[y][x] - '0');
            }
        }
    }

    void partA() {
        if(grid.size() <= 0) loadGrid();
        partASolution = 0;

        partASolution = dijkstra::dijkstraSearch(grid, dijkstra::position { 0, 0, dijkstra::direction::NONE, 1 }, dijkstra::position { grid[0].size() - 1, grid.size() - 1 });
    }

    void partB() {
        partBSolution = 0;
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day17() : Day("input/day17.txt") {}
};

#endif