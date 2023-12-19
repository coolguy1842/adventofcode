#ifndef __DAY17_HPP__
#define __DAY17_HPP__

#include <queue>

#include <day.hpp>
#include <stdio.h>

namespace dijkstra {
    
struct position {
    size_t x;
    size_t y;
        
    bool operator==(const position& pos) { return x == pos.x && y == pos.y; }
    bool operator==(const position& pos) const { return x == pos.x && y == pos.y; }
}; 


struct position_hash {
    inline std::size_t operator()(const position& c) const {
        return (c.x << 32) + c.y;
    }
};


struct cell {
    struct dijkstra::position position;
    int heatLoss;

    int lowest = __INT_MAX__;
};

enum direction {
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
    NONE
};

struct neighbour {
    dijkstra::cell* cell;
    dijkstra::direction direction;
};

std::vector<neighbour> getValidNeighbours(position& pos, std::vector<dijkstra::neighbour> path, std::vector<std::vector<cell>>& grid, const size_t& width, const size_t& height) {
    std::vector<neighbour> neighbours;

    size_t lastDirChange = path.size();
    for(long long i = (long long)path.size() - 1; i > 0; i--) {
        dijkstra::neighbour right = path[i], left = path[i - 1];
        if(right.direction != left.direction) {
            lastDirChange = path.size() - i;
            break;
        }
    }

    if(lastDirChange < 3) {
        if(pos.y > 0) neighbours.push_back({ &grid[pos.y - 1][pos.x], dijkstra::direction::NORTH });
        if(pos.y < height - 1) neighbours.push_back({ &grid[pos.y + 1][pos.x], dijkstra::direction::SOUTH });

        if(pos.x > 0) neighbours.push_back({ &grid[pos.y][pos.x - 1], dijkstra::direction::WEST });
        if(pos.x < width - 1) neighbours.push_back({ &grid[pos.y][pos.x + 1], dijkstra::direction::EAST });

        return neighbours;
    }


    dijkstra::neighbour& prev = path[path.size() - 2];
    if(prev.direction != dijkstra::direction::NORTH && pos.y > 0) neighbours.push_back({ &grid[pos.y - 1][pos.x], dijkstra::direction::NORTH });
    if(prev.direction != dijkstra::direction::SOUTH && pos.y < height - 1) neighbours.push_back({ &grid[pos.y + 1][pos.x], dijkstra::direction::SOUTH });
    
    if(prev.direction != dijkstra::direction::WEST && pos.x > 0) neighbours.push_back({ &grid[pos.y][pos.x - 1], dijkstra::direction::WEST });
    if(prev.direction != dijkstra::direction::EAST && pos.x < width - 1) neighbours.push_back({ &grid[pos.y][pos.x + 1], dijkstra::direction::EAST });

    return neighbours;
}

int dijkstraSearch(struct std::vector<std::vector<dijkstra::cell>>& grid, const struct position& start, const struct position& dest, int maxScore = __INT_MAX__) {
    struct queueContents {
        dijkstra::cell* cell;
        int totalCost = 0;
        
        std::vector<dijkstra::neighbour> path;
        
        bool operator>(const queueContents& qC) const { return totalCost > qC.totalCost; }
    };

    std::priority_queue<queueContents, std::vector<queueContents>, std::greater<queueContents>> queue;
    robin_hood::unordered_flat_map<dijkstra::position, size_t, dijkstra::position_hash> dists;
    for(size_t y : range(grid.size())) for(size_t x : range(grid[0].size())) dists[{ x, y }] = maxScore;
    
    queueContents end = { &grid[dest.y][dest.x], maxScore };
    queue.push({ &grid[start.y][start.x], 0, { { &grid[start.y][start.x], NONE } } });
        
    while (!queue.empty()) {
        const struct queueContents cur = queue.top();
        queue.pop();

        for (dijkstra::neighbour& neighbour : getValidNeighbours(cur.cell->position, cur.path, grid, grid[0].size(), grid.size())) {
            if(dists[neighbour.cell->position] < cur.totalCost + neighbour.cell->heatLoss) continue;
               
            dists[neighbour.cell->position] = cur.totalCost + neighbour.cell->heatLoss;
            if(neighbour.cell->position == dest && end.totalCost > dists[neighbour.cell->position]) {
                end.totalCost = dists[neighbour.cell->position];
                
                auto newPath = cur.path;
                newPath.push_back(neighbour);

                end.path = newPath;

                continue;
            }

            
            auto newPath = cur.path;
            newPath.push_back(neighbour);

            queue.push({ neighbour.cell, cur.totalCost + neighbour.cell->heatLoss, newPath });
        }
    }


    for(size_t y : range(grid.size())) {
        for(size_t x : range(grid[0].size())) {
            bool found = false;
            for(size_t c : range(end.path.size())) {
                auto cur = end.path[c];

                if(cur.cell->position.x == x && cur.cell->position.y == y) {
                    if(c == 0) {
                        printf("#");
                        found = true;
                        continue;
                    }
                    
                    
                    auto prev = end.path[c - 1];

                    if(cur.cell->position.x > prev.cell->position.x) printf(">");
                    else if(cur.cell->position.x < prev.cell->position.x) printf("<");
                    else if(cur.cell->position.y > prev.cell->position.y) printf("v");
                    else if(cur.cell->position.y < prev.cell->position.y) printf("^");
                    else {
                        printf("#");
                    }

                    found = true;
                    break;
                }
            }

            if(!found) printf("%d", grid[y][x].heatLoss);
        }

        printf("\n");
    }

    printf("\n\n\n");

    return end.totalCost;
}

};

class Day17 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    std::vector<std::vector<dijkstra::cell>> grid = {};

public:
    void loadGrid() {
        grid = std::vector<std::vector<dijkstra::cell>>(input.size(), std::vector<dijkstra::cell>());

        for(size_t y = 0; y < input.size(); y++) {
            for(size_t x = 0; x < input[0].size(); x++) {
                dijkstra::cell cell = {};

                int heatLoss = this->input[y][x] - '0';
                cell.position = {x, y};
                cell.heatLoss = heatLoss;

                grid[y].push_back(cell);
            }
        }
    }

    void partA() {
        if(grid.size() <= 0) loadGrid();
        partASolution = 0;

        partASolution = dijkstra::dijkstraSearch(grid, dijkstra::position { 0, 0 }, dijkstra::position { grid[0].size() - 1, grid.size() - 1 });
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