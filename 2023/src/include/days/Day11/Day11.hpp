#ifndef __DAY11_HPP__
#define __DAY11_HPP__

#include <day.hpp>
#include <stdio.h>

#include <cmath>

#include <util/helperStructs.hpp>

struct Galaxy {
    size_t number;
    Coordinates coords;

    size_t distance(const Galaxy& from) const {
        return std::abs(coords.x - from.coords.x) + std::abs(coords.y - from.coords.y);
    }
};

class Day11 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    std::vector<Galaxy> galaxies;
    std::vector<size_t> rowOffsets;
    std::vector<size_t> colOffsets;

public:
    bool rowEmpty(const size_t& row, const std::vector<std::string>& input) {
        return !input[row].contains('#');
    }
    
    bool colEmpty(const size_t& col, const std::vector<std::string>& input) {
        for(size_t y = 0; y < input.size(); y++) {
            if(input[y][col] == '#') return false;
        }

        return true;
    }

    void loadGalaxies(size_t expansion) {
        if(expansion > 1) expansion--;

        galaxies = {};

        colOffsets.clear();
        colOffsets.reserve(input[0].size());
        
        rowOffsets.clear();
        rowOffsets.reserve(input.size());

        size_t curColOffset = 0;
        for(size_t col = 0; col < input[0].size() - 1; col++) {
            colOffsets[col] = curColOffset;
            if(colEmpty(col, input)) curColOffset += expansion;
        }

        size_t curRowOffset = 0;
        for(size_t row = 0; row < input.size(); row++) {
            rowOffsets[row] = curRowOffset;
            if(rowEmpty(row, input)) curRowOffset += expansion;
        }

        size_t nextID = 1;
        for(size_t i = 0; i < input.size(); i++) {
            size_t rowOffset = rowOffsets[i];
            for(size_t j = 0; j < input[0].size(); j++) {
                if(input[i][j] != '#') continue;
                size_t colOffset = colOffsets[j];

                Coordinates coords = Coordinates(j + colOffset, i + rowOffset);
                Galaxy galaxy = { nextID++, coords};

                galaxies.push_back(galaxy);
            }
        }
    }

    void partA() {
        loadGalaxies(1);
        partASolution = 0;

        for(const Galaxy& galaxy : galaxies) {
            for(size_t j = galaxy.number; j < galaxies.size(); j++) {
                const Galaxy& other = galaxies[j];
                partASolution += galaxy.distance(other);
            }
        }
    }

    void partB() {
        loadGalaxies(1000000);
        partBSolution = 0;

        for(const Galaxy& galaxy : galaxies) {
            for(size_t j = galaxy.number; j < galaxies.size(); j++) {
                const Galaxy& other = galaxies[j];
                partBSolution += galaxy.distance(other);
            }
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day11() : Day("input/day11.txt") {}
};

#endif