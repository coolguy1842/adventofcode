#ifndef __DAY3_HPP__
#define __DAY3_HPP__

#include <spdlog/spdlog.h>
#include <day.hpp>

#include <robin_hood.hpp>

#include <array>
#include <vector>

enum PositionType {
    EMPTY = 0,
    SYMBOL,
    NUMBER
};

struct Position {
    PositionType type;
    char c;

    int x;
    int y;
};

struct pair_hash {
    inline std::size_t operator()(const robin_hood::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

class Day3 : public AOC::Day {
private:
    int partASolution;
    int partBSolution;

    std::vector<std::vector<Position>> map;

public:
    void loadMap(const size_t width, const size_t height) {
        this->map = std::vector<std::vector<Position>>(height);

        for(int y = 0; y < (int)height; y++) {
            map[y].reserve(width);

            for(int x = 0; x < (int)width; x++) {
                char c = input[y][x];

                if(isdigit(c)) map[y][x] = Position { PositionType::NUMBER, c, x, y };
                else if(c == '.') map[y][x] = Position { PositionType::EMPTY, c, x, y };
                else map[y][x] = Position { PositionType::SYMBOL, c, x, y };
            }
        }
    }


    int getNumber(robin_hood::unordered_flat_set<robin_hood::pair<int, int>, pair_hash>& found, size_t width, size_t height, int x, int y) {
        if(found.contains(robin_hood::pair<int, int>{x, y}) || map[y][x].type != PositionType::NUMBER) return 0;
        int out = 0, minX = 0;

        for(minX = x; minX >= 0; minX--) {
            if(map[y][minX].type != PositionType::NUMBER) break;
        }

        for(int i = minX + 1; i < (int)width; i++) {
            Position pos = map[y][i];

            if(pos.type != PositionType::NUMBER) break;
        
            out *= 10;
            out += pos.c - '0';

            found.insert(robin_hood::pair<int, int>{pos.x, pos.y});
        }

        return out;
    }

    void partA() {
        partASolution = 0;
        
        long long width = (long long)input[0].size(), height = (long long)input.size();
        if(map.size() <= 0) loadMap(width, height);

        robin_hood::unordered_flat_set<robin_hood::pair<int, int>, pair_hash> found;

        for(long long y = 0; y < height; y++) {
            for(long long x = 0; x < width; x++) {
                if(map[y][x].type != PositionType::SYMBOL) continue;

                for(int i = -1; i <= 1; i++) {
                    for(int j = -1; j <= 1; j++) {
                        partASolution += getNumber(found, width, height, x + i, y + j);
                    }   
                }
            }
        }
    }
    
    void partB() {
        partBSolution = 0;
        
        long long width = (long long)input[0].size(), height = (long long)input.size();
        if(map.size() <= 0) loadMap(width, height);

        robin_hood::unordered_flat_set<robin_hood::pair<int, int>, pair_hash> found;

        for(long long y = 0; y < height; y++) {
            for(long long x = 0; x < width; x++) {
                if(map[y][x].type != PositionType::SYMBOL && map[y][x].c != '*') continue;

                std::vector<int> values;

                for(int i = -1; i <= 1; i++) {
                    for(int j = -1; j <= 1; j++) {
                        int value = getNumber(found, width, height, x + i, y + j);
                        if(value <= 0) continue;

                        values.push_back(value);
                    }   
                }

                if(values.size() != 2) continue;
                partBSolution += values[0] * values[1];
            }
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) spdlog::info("partA: {}", partASolution);
        if(partB) spdlog::info("partB: {}", partBSolution);
    }

    Day3() : Day("input/day3.txt") {}
};

#endif