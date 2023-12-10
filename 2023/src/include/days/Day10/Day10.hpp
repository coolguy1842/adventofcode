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
    unsigned int directions;
    char c;

    Coordinates coords;

    Pipe(char c, long x, long y) {
        this->coords.x = x;
        this->coords.y = y;

        this->c = c;

        this->loadDirections();
    }
};

class Day10 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    robin_hood::unordered_flat_map<Coordinates, Pipe> pipes;

public:
    void loadPipes() {

    }

    void partA() {
        if(pipes.size() <= 0) loadPipes();
        partASolution = 0;
    }

    void partB() {
        if(pipes.size() <= 0) loadPipes();
        partBSolution = 0;
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day10() : Day("input/day10.txt") {}
};

#endif