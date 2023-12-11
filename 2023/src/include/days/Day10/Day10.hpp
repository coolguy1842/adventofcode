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

    Coordinates nextPipe(Coordinates from, robin_hood::unordered_flat_set<Coordinates, coordinates_hash>& travelled) {
        const Pipe& current = grid[from.y][from.x];

        if(current.hasSouth()) {
            const Pipe& next = grid[from.y + 1][from.x];
            if(next.isPipe() && next.hasNorth() && !travelled.contains(next.coords)) {
                if(current.c != 'S') travelled.emplace(from);
                return next.coords;
            }
        }

        if(current.hasEast()) {
            const Pipe& next = grid[from.y][from.x + 1];

            if(next.isPipe() && next.hasWest() && !travelled.contains(next.coords)) {
                if(current.c != 'S') travelled.emplace(from);
                return next.coords;
            }
        }
        
        if(current.hasNorth()) {
            const Pipe& next = grid[from.y - 1][from.x];
            if(next.isPipe() && next.hasSouth() && !travelled.contains(next.coords)) {
                if(current.c != 'S') travelled.emplace(from);
                return next.coords;
            }
        }
        
        if(current.hasWest()) {
            const Pipe& next = grid[from.y][from.x - 1];
            if(next.isPipe() && next.hasEast() && !travelled.contains(next.coords)) {
                if(current.c != 'S') travelled.emplace(from);
                return next.coords;
            }
        }


        return from;
    }

    size_t findFurthestDistance(Coordinates start) {
        robin_hood::unordered_flat_set<Coordinates, coordinates_hash> travelled;
        size_t out = 0;

        Coordinates cur = start;
        do {
            grid[cur.y][cur.x].inMainLoop = true;
            out++;
        } while((cur = nextPipe(cur, travelled)) != start);

        return out / 2;
    }

    void partA() {
        if(grid.size() <= 0) loadGrid();
        partASolution = findFurthestDistance(animalStart);

        for(size_t y = 0; y < input.size(); y++) {
            for(size_t x = 0; x < input[0].size(); x++) {
                const Pipe& pipe = grid[y][x];
                
                if(pipe.isPipe() && !pipe.inMainLoop) printf("#");
                else printf("%c", input[y][x]);
            }

            printf("\n");
        }
    }


    bool isEnclosed(Coordinates coords, robin_hood::unordered_flat_set<Coordinates, coordinates_hash>& checked) {
        checked.emplace(coords);

        if(coords.x + 1 >= (long)grid[0].size() || coords.x - 1 < 0 || coords.y + 1 >= (long)grid.size() || coords.y - 1 < 0) return false;

        for(int i = -1; i <= 1; i += 2) {
            Pipe pipe = grid[coords.y][coords.x + i];
            if(!pipe.isPipe() && !checked.contains(pipe.coords)) {
                if(!isEnclosed(pipe.coords, checked)) return false;
            }

            pipe = grid[coords.y + i][coords.x];
            if(!pipe.isPipe() && !checked.contains(pipe.coords)) {
                if(!isEnclosed(pipe.coords, checked)) return false;
            }
        }
        
        return true;
    }

    size_t enclosedCount(const Coordinates& coords, robin_hood::unordered_flat_set<Coordinates, coordinates_hash>& found) {
        size_t out = 1;

        found.emplace(coords);

        for(int i = -1; i <= 1; i += 2) {
            Coordinates coord = Coordinates(coords.x + i, coords.y);
            if(coord.x >= 0 && coord.x < (int)input[0].size()) {
                if(!grid[coord.y][coord.x].isPipe() && !found.contains(coord)) {
                    out += enclosedCount(coord, found);
                }
            }
            
            coord = Coordinates(coords.x, coords.y + i);
            if(coord.y >= 0 && coord.y < (int)input.size()) {
                if(!grid[coord.y][coord.x].isPipe() && !found.contains(coord)) {
                    out += enclosedCount(coord, found);
                }
            }
        }

        return out;
    }

    void partB() {
        robin_hood::unordered_flat_set<Coordinates, coordinates_hash> found;
        robin_hood::unordered_flat_set<Coordinates, coordinates_hash> checked;

        if(grid.size() <= 0) loadGrid();
        partBSolution = 0;
        
         for(long y = 0; y < (long)grid.size(); y++) {
            for(long x = 0; x < (long)grid[0].size(); x++) {
                Pipe& pipe = grid[y][x];

                if(pipe.isPipe() && !pipe.inMainLoop) {
                    pipe.c = '.';
                    pipe.directions = 0;
                }
            }
        }

        for(long y = 0; y < (long)grid.size(); y++) {
            for(long x = 0; x < (long)grid[0].size(); x++) {
                Pipe& pipe = grid[y][x];

                if(pipe.isPipe()) continue;
                if(found.contains(pipe.coords) || checked.contains(pipe.coords)) continue;
                if(!isEnclosed(pipe.coords, checked)) continue;

                partBSolution += enclosedCount(pipe.coords, found);
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