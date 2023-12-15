#ifndef __DAY3_HPP__
#define __DAY3_HPP__

#include <day.hpp>
#include <util/helperStructs.hpp>

#include <robin_hood.hpp>

#include <array>
#include <vector>

enum PositionType {
    NONE = 0,
    SYMBOL,
    NUMBER
};

struct Position {
    PositionType type;
    char c;

    Coordinates coords;
};

class Day3 : public AOC::Day {
private:
    int partASolution;
    int partBSolution;

    std::vector<std::vector<Position>> map;
    int mapWidth;
    int mapHeight;

    size_t mapWidthULL;
    size_t mapHeightULL;

public:
    void loadMap() {
        mapWidthULL = input[0].size(), mapHeightULL = input.size();
        mapWidth = (long)mapWidthULL, mapHeight = (long)mapHeightULL;
        
        this->map = std::vector<std::vector<Position>>(mapHeightULL);

        for(int y = 0; y < mapHeight; y++) {
            map[y].reserve(mapHeightULL);

            for(int x = 0; x < mapWidth; x++) {
                char c = input[y][x];

                if(isdigit(c)) map[y][x] = { PositionType::NUMBER, c, x, y };
                else if(c == '.') map[y][x] = { PositionType::NONE, c, x, y };
                else map[y][x] = { PositionType::SYMBOL, c, x, y };
            }
        }
    }

    int getNumber(robin_hood::unordered_flat_set<Coordinates, coordinates_hash>& found, int x, int y) {
        if(x < 0 || x >= mapWidth || y < 0 || y >= mapHeight || found.contains({x, y}) || map[y][x].type != PositionType::NUMBER) return 0;
        int out = 0, minX = x;

        while(map[y][--minX].type == PositionType::NUMBER);

        for(long i = minX + 1; i < mapWidth; i++) {
            Position pos = map[y][i];
            if(pos.type != PositionType::NUMBER) break;
        
            out *= 10;
            out += pos.c - '0';

            found.insert(pos.coords);
        }

        return out;
    }


    void partA() {
        if(map.size() <= 0) loadMap();
        partASolution = 0;
        
        robin_hood::unordered_flat_set<Coordinates, coordinates_hash> found;

        for(long y = 0; y <  mapHeight; y++) {
            for(long x = 0; x < mapWidth; x++) {
                if(map[y][x].type != PositionType::SYMBOL) continue;

                for(int i = 0; i < 9; i++) {
                    partASolution += getNumber(found, x + (i % 3) - 1, y + (i / 3) - 1);
                }
            }
        }
    }
    
    void partB() {
        if(map.size() <= 0) loadMap();
        partBSolution = 0;
        
        robin_hood::unordered_flat_set<Coordinates, coordinates_hash> found;

        for(long long y = 0; y < mapHeight; y++) {
            for(long long x = 0; x < mapWidth; x++) {
                if(map[y][x].type != PositionType::SYMBOL && map[y][x].c != '*') continue;
                std::vector<int> values;

                for(int i = 0; i < 9; i++) {
                    int value = getNumber(found, x + ((i % 3) - 1), y + ((i / 3) - 1));
                    if(value <= 0) continue;

                    values.push_back(value);
                }
                
                if(values.size() != 2) continue;
                partBSolution += values[0] * values[1];
            }
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %d\n", partASolution);
        if(partB) printf("partB: %d\n", partBSolution);
    }

    Day3() : Day("input/day3.txt") {}
};

#endif