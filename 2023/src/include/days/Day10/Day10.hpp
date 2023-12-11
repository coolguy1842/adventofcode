#ifndef __DAY10_HPP__
#define __DAY10_HPP__

#include <day.hpp>
#include <stdio.h>

#include <util/helperStructs.hpp>
#include <robin_hood.hpp>

enum PipeDirection {
    NORTH = 1 << 0,
    SOUTH = 1 << 1,
    WEST =  1 << 2,
    EAST =  1 << 3,
};

struct Pipe {
private:
    void loadDirections() {
        switch(c) {
        case '|': this->directions = NORTH | SOUTH; break;
        case '-': this->directions = WEST  |  EAST; break;
        case 'L': this->directions = NORTH |  EAST; break;
        case 'J': this->directions = NORTH |  WEST; break;
        case '7': this->directions = SOUTH |  WEST; break;
        case 'F': this->directions = SOUTH |  EAST; break;
        case 'S': this->directions =        0xFFFF; break;
        default: directions = 0;
        }
    }

public:
    bool isPipe() const { return this->directions != 0;}
    unsigned int directions;
    char c;

    bool inMainLoop;
    Coordinates coords;

    Pipe(char c, long x, long y) : c(c), inMainLoop(false), coords(Coordinates(x, y)) {
        this->loadDirections();
    }
    Pipe() : directions(0), c('.'), inMainLoop(false), coords(Coordinates(0, 0)) {}

    bool hasNorth() const { return directions & NORTH; }
    bool hasSouth() const   { return directions & SOUTH; }

    bool hasEast() const { return directions & EAST; }
    bool hasWest() const { return directions & WEST; }
};

class Day10 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    std::vector<std::vector<Pipe>> grid;
    std::vector<Coordinates> verts;
    
    Coordinates animalStart;

public:
    void loadGrid() {
        for(size_t y = 0; y < input.size(); y++) {
            grid.push_back({});

            for(size_t x = 0; x < input[0].size(); x++) {
                grid[y].push_back(Pipe(input[y][x], (long)x, (long)y));

                if(input[y][x] == 'S') animalStart = Coordinates(x, y);
            }
        }
    }

    void findPipes(Coordinates from) {
        const Pipe& current = grid[from.y][from.x];

        if(current.hasSouth() && from.y + 1 < (long)grid.size()) {
            Pipe& next = grid[from.y + 1][from.x];
            if(next.isPipe() && next.hasNorth() && !next.inMainLoop) {
                verts.push_back(next.coords);
                next.inMainLoop = true;
                findPipes(next.coords);
            }
        }

        if(current.hasEast()  && from.x + 1 < (long)grid[0].size()) {
            Pipe& next = grid[from.y][from.x + 1];
            if(next.isPipe() && next.hasWest() && !next.inMainLoop) {
                verts.push_back(next.coords);
                next.inMainLoop = true;
                findPipes(next.coords);
            }
        }
        
        if(current.hasNorth() && from.y - 1 >= 0) {
            Pipe& next = grid[from.y - 1][from.x];
            if(next.isPipe() && next.hasSouth() && !next.inMainLoop) {
                verts.push_back(next.coords);
                next.inMainLoop = true;
                findPipes(next.coords);
            }
        }
        
        if(current.hasWest() && from.x - 1 >= 0) {
            Pipe& next = grid[from.y][from.x - 1];
            if(next.isPipe() && next.hasEast() && !next.inMainLoop) {
                verts.push_back(next.coords);
                next.inMainLoop = true;
                findPipes(next.coords);
            }
        }
    }

    size_t findFurthestDistance(Coordinates start) {
        robin_hood::unordered_flat_set<Coordinates, coordinates_hash> travelled;
        size_t out = 0;

        findPipes(start);

        for(size_t y = 0; y < grid.size(); y++) {
            for(size_t x = 0; x < grid[0].size(); x++) {
                Pipe& pipe = grid[y][x];

                if(pipe.isPipe()) {
                    if(pipe.inMainLoop) out++;
                    else {
                        pipe.c = '.';
                        pipe.directions = 0;
                    }
                }
            }   
        }

        return out / 2;
    }

    void partA() {
        if(grid.size() <= 0) loadGrid();
        partASolution = findFurthestDistance(animalStart);
    }

    bool isEnclosed(Coordinates coords) {
        size_t j = verts.size() - 1;
        bool ret = false;

        for(size_t i = 0; i < verts.size(); i++) {
            if (coords == verts[i]) return true;

            if ((verts[i].y > coords.y) != (verts[j].y > coords.y)) {
                long slope = (coords.x - verts[i].x) * (verts[j].y - verts[i].y) - (verts[j].x - verts[i].x) * (coords.y - verts[i].y);

                if(slope == 0) return true;
                if((slope < 0) != (verts[j].y < verts[i].y)) ret = !ret;
            }

            j = i;
        }

        return ret;
    }

    void partB() {
        if(grid.size() <= 0) {
            loadGrid();
            // load main pipe system and verts
            findFurthestDistance(animalStart);
        }

        partBSolution = 0;
        
        for(long y = 0; y < (long)grid.size(); y++) {
            for(long x = 0; x < (long)grid[0].size(); x++) {
                Pipe& pipe = grid[y][x];

                if(!pipe.isPipe()) {
                    partBSolution += isEnclosed(pipe.coords);
                }
            }
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day10() : Day("input/day10.txt") {}
};

#endif