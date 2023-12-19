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

std::array<cell*, 4> getValidNeighbours(position& pos, std::vector<dijkstra::cell*> prevCells, std::vector<std::vector<cell>>& grid, const size_t& width, const size_t& height) {
    std::array<cell*, 4> neighbours = {nullptr, nullptr, nullptr, nullptr};

    size_t lastDirChange = prevCells.size();
    for(long long i = (long long)prevCells.size() - 2; i > 0; i--) {
        cell* right = prevCells[i + 1], *mid = prevCells[i], *left = prevCells[i - 1];
        if(left->position.x != right->position.x && left->position.y != right->position.y) {
            lastDirChange = prevCells.size() - i;
            break;
        }
    }

    if(lastDirChange <= 3) {
        if(pos.x > 0) neighbours[0] = &grid[pos.y][pos.x - 1];
        if(pos.x < width - 1) neighbours[1] = &grid[pos.y][pos.x + 1];

        if(pos.y > 0) neighbours[2] = &grid[pos.y - 1][pos.x];
        if(pos.y < height - 1) neighbours[3] = &grid[pos.y + 1][pos.x];

        return neighbours;
    }


    cell* lastDirCell = prevCells[prevCells.size() - 2];
    if(lastDirCell->position.y != pos.y && pos.x > 0) neighbours[0] = &grid[pos.y][pos.x - 1];
    if(lastDirCell->position.y != pos.y && pos.x < width - 1) neighbours[1] = &grid[pos.y][pos.x + 1];
    
    if(lastDirCell->position.x != pos.x && pos.y > 0) neighbours[2] = &grid[pos.y - 1][pos.x];
    if(lastDirCell->position.x != pos.x && pos.y < height - 1) neighbours[3] = &grid[pos.y + 1][pos.x];

    return neighbours;
}

int dijkstraSearch(struct std::vector<std::vector<dijkstra::cell>>& grid, const struct position& start, const struct position& dest, int maxScore = __INT_MAX__) {
    struct queueContents {
        cell* cell;
        int totalCost = 0;
        
        std::vector<dijkstra::cell*> prevCells;
        robin_hood::unordered_flat_set<dijkstra::position, dijkstra::position_hash> travelled;

        bool operator>(const queueContents& qC) const { return totalCost > qC.totalCost; }
    };

    
    /*std::priority_queue<queueContents, std::vector<queueContents>, std::greater<queueContents>> queue;
    

    struct position pos = start;
    queue.emplace(&grid[pos.y][pos.x]);

    struct cell* curCell;
    while(!queue.empty()) {
        const struct queueContents qC = queue.top();
        queue.pop();

        curCell = qC.cell;
        const int& totalCost = qC.totalCost;

        
        if(curCell->visited) continue;
        curCell->visited = true;
        
        if(totalCost > maxScore) continue;
        auto prev = qC.prevCells;
        prev.push_back(curCell);

        auto neighbours = getValidNeighbours(curCell->position, prev, grid, grid[0].size(), grid.size());
        for(cell* cell : neighbours) {
            if(!cell) continue;
            if(cell->position == dest) {
                for(size_t y : range(grid.size())) {
                    for(size_t x : range(grid[0].size())) {
                        bool found = false;
                        for(auto c : prev) {
                            if(c->position.x == x && c->position.y == y) {
                                printf("#");

                                found = true;
                                break;
                            }
                        }

                        if(!found) printf("%d", grid[y][x].heatLoss);
                    }

                    printf("\n");
                }

                return totalCost + cell->heatLoss;
            }

            queue.emplace(cell, totalCost + cell->heatLoss, prev);
        }*/

    std::priority_queue<queueContents, std::vector<queueContents>, std::greater<queueContents>> queue;
    int end = maxScore;

    queue.push({ &grid[start.y][start.x], 0, {} });

    while (!queue.empty()) {
        const struct queueContents cur = queue.top();
        queue.pop();

        auto newPrev = cur.prevCells;
        auto newTravelled = cur.travelled;
        newPrev.push_back(cur.cell);
        newTravelled.emplace(cur.cell->position);

        /*
        for(size_t y : range(grid.size())) {
            for(size_t x : range(grid[0].size())) {
                bool found = false;
                for(size_t c : range(newPrev.size())) {
                    auto cur = newPrev[c];

                    if(cur->position.x == x && cur->position.y == y) {
                        if(c == 0) {
                            printf("#");
                            found = true;
                            continue;
                        }
                        
                        
                        auto prev = newPrev[c - 1];

                        if(cur->position.x > prev->position.x) printf(">");
                        else if(cur->position.x < prev->position.x) printf("<");
                        else if(cur->position.y > prev->position.y) printf("v");
                        else if(cur->position.y < prev->position.y) printf("^");
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
        //*/
        for (cell* cell : getValidNeighbours(cur.cell->position, newPrev, grid, grid[0].size(), grid.size())) {
            if(cell == nullptr || newTravelled.contains(cell->position)) continue;

            if(cell->position == dest) {
                end = std::min(end, cur.totalCost + cell->heatLoss);
                continue;
            }
            
            newTravelled.emplace(cell->position);

            queue.push({ cell, cur.totalCost + cell->heatLoss, newPrev, newTravelled });
        }
    }

    return end;
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