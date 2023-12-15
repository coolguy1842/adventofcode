#ifndef __DAY14_HPP__
#define __DAY14_HPP__

#include <util/range.hpp>

#include <day.hpp>
#include <stdio.h>

class Grid {
public:
    enum GridObject {
        CUBE = '#',
        ROUND = 'O',
        EMPTY = '.'
    };

    enum Direction {
        NORTH = 0,
        SOUTH,
        EAST,
        WEST
    };

private:
    std::vector<std::vector<GridObject>> grid;

    void flipNorth() {
        for(size_t y : range(1ULL, grid.size())) {
            for(size_t x : range(grid[0].size())) {
                if(grid[y][x] != GridObject::ROUND) continue;
                if(grid[y - 1][x] != GridObject::EMPTY) continue;

                for(long long newY = y; newY >= 0; newY--) {
                    if(newY == 0) {
                        grid[newY][x] = GridObject::ROUND;
                        grid[y][x] = GridObject::EMPTY;
                        break;
                    }

                    if(grid[newY - 1][x] != GridObject::EMPTY) {
                        grid[newY][x] = GridObject::ROUND;
                        grid[y][x] = GridObject::EMPTY;
                        break;
                    }
                }
            }
        }
    }

    void flipSouth() {
        for(long long y = grid.size() - 2; y >= 0; y--) {
            for(size_t x : range(grid[0].size())) {
                if(grid[y][x] != GridObject::ROUND) continue;
                if(grid[y + 1][x] != GridObject::EMPTY) continue;

                for(size_t newY = y; newY < grid.size(); newY++) {
                    if(newY == grid.size() - 1) {
                        grid[newY][x] = GridObject::ROUND;
                        grid[y][x] = GridObject::EMPTY;
                        break;
                    }

                    if(grid[newY + 1][x] != GridObject::EMPTY) {
                        grid[newY][x] = GridObject::ROUND;
                        grid[y][x] = GridObject::EMPTY;
                        break;
                    }
                }
            }
        }
    }

    
    void flipEast() {
        for(long long x = grid[0].size() - 2; x >= 0; x--) {
            for(size_t y : range(grid.size())) {
                if(grid[y][x] != GridObject::ROUND) continue;
                if(grid[y][x + 1] != GridObject::EMPTY) continue;

                for(size_t newX = x; newX < grid[0].size(); newX++) {
                    if(newX == grid[0].size() - 1) {
                        grid[y][newX] = GridObject::ROUND;
                        grid[y][x] = GridObject::EMPTY;
                        break;
                    }

                    if(grid[y][newX + 1] != GridObject::EMPTY) {
                        grid[y][newX] = GridObject::ROUND;
                        grid[y][x] = GridObject::EMPTY;
                        break;
                    }
                }
            }
        }
    }

    void flipWest() {
        for(size_t x : range(1ULL, grid[0].size())) {
            for(size_t y : range(grid.size())) {
                if(grid[y][x] != GridObject::ROUND) continue;
                if(grid[y][x - 1] != GridObject::EMPTY) continue;

                for(long long newX = x; newX >= 0; newX--) {
                    if(newX == 0) {
                        grid[y][newX] = GridObject::ROUND;
                        grid[y][x] = GridObject::EMPTY;
                        break;
                    }

                    if(grid[y][newX - 1] != GridObject::EMPTY) {
                        grid[y][newX] = GridObject::ROUND;
                        grid[y][x] = GridObject::EMPTY;
                        break;
                    }
                }
            }
        }
    }

public:
    std::vector<std::vector<GridObject>>& getGrid() { return grid; }
    Grid(const std::vector<std::vector<GridObject>>& grid) : grid(grid) {}
    Grid() : grid({}) {}

    void flipGrid(Direction direction) {
        switch(direction) {
        case NORTH: flipNorth(); break;
        case SOUTH: flipSouth(); break;
        case EAST: flipEast(); break;
        case WEST: flipWest(); break;
        default: break;
        }
    }
};


class Day14 : public AOC::Day {
private:
    Grid grid;
    Grid gridB;

    size_t partASolution;
    size_t partBSolution;
    
public:
    void loadGrid() {
        std::vector<std::vector<Grid::GridObject>> map;

        for(size_t y : range(input.size())) {
            std::vector<Grid::GridObject> row;

            for(size_t x : range(input[0].size())) {
                row.push_back((Grid::GridObject)input[y][x]);
            }

            map.push_back(row);
        }

        this->grid = Grid(map);
        this->gridB = this->grid;
    }


    void partA() {
        if(grid.getGrid().size() <= 0) loadGrid();
        partASolution = 0;

        grid.flipGrid(Grid::Direction::NORTH);

        auto map = grid.getGrid();
        for(size_t y : range(map.size())) {
            auto row = map[y];

            partASolution += std::accumulate(row.begin(), row.end(), 0, [](size_t cur, const Grid::GridObject& obj){ return cur + (obj == Grid::GridObject::ROUND); }) * (map.size() - y);
        }
    }

    void partB() {
        if(grid.getGrid().size() <= 0) loadGrid();
        partBSolution = 0;

        std::vector<std::vector<Grid::GridObject>> prev = gridB.getGrid();
        for([[maybe_unused]] size_t i : range(1000)) {
            gridB.flipGrid(Grid::Direction::NORTH);
            gridB.flipGrid(Grid::Direction::WEST);
            gridB.flipGrid(Grid::Direction::SOUTH);
            gridB.flipGrid(Grid::Direction::EAST);
        }

        auto map = gridB.getGrid();
        for(size_t y : range(map.size())) {
            auto row = map[y];

            partBSolution += std::accumulate(row.begin(), row.end(), 0, [](size_t cur, const Grid::GridObject& obj){ return cur + (obj == Grid::GridObject::ROUND); }) * (map.size() - y);
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day14() : Day("input/day14.txt") {}
};

#endif