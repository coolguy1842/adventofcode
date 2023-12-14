#ifndef __DAY13_HPP__
#define __DAY13_HPP__

#include <util/range.hpp>

#include <day.hpp>
#include <stdio.h>


enum MapObject {
    ASH = 0,
    ROCK
};

class Map {
public:
    std::vector<std::vector<MapObject>> rows;

private:
    bool vertical = false;
    bool directionKnown = false;

    size_t verticalMiddle;
    size_t horizontalMiddle;

    std::string verticalString(size_t i) {
        std::string out = "";
        
        for(size_t j : range(rows.size())) {
            out += rows[j][i];
        }

        return out;
    }


    void loadHorizontal() {
        for(long long i = (long long)rows.size() - 2; i >= 0; i--) {
            if(rows[i] == rows[i + 1]) {
                size_t middle = i;

                bool isValid = true;
                long long left, right;
                for(left = middle, right = middle + 1; left >= 0 && right < (long long)rows.size(); left--, right++) {
                    if(rows[left] != rows[right]) {
                        isValid = false;
                        break;
                    }
                }

                if((left <= 0 || right >= (long long)rows.size() - 1) && isValid) {
                    vertical = false;
                    directionKnown = true;
                    
                    horizontalMiddle = middle;
                    return;
                }                
            }
        }
    }
    
    void loadVertical() {
        for(long long i = (long long)rows[0].size() - 2; i >= 0; i--) {
            if(verticalString(i) == verticalString(i + 1)) {
                size_t middle = i;
                
                bool isValid = true;
                long long left, right;
                for(left = middle, right = middle + 1; left >= 0 && right < (long long)rows[0].size(); left--, right++) {
                    if(verticalString(left) != verticalString(right)) {
                        isValid = false;
                        break;
                    }
                }

                if((left <= 0 || right >= (long long)rows[0].size() - 1) && isValid) {
                    vertical = true;
                    directionKnown = true;

                    verticalMiddle = middle;
                    return;
                }
            }
        }
    }

public:
    std::vector<std::vector<MapObject>> getRows() { return rows; }

    bool isVertical() const { return vertical; }
    bool isHorizontal() const { return !vertical; }
    
    size_t getVerticalMiddle() const { return verticalMiddle; }
    size_t getHorizontalMiddle() const { return horizontalMiddle; }

    Map(std::vector<std::vector<MapObject>> rows) : rows(rows) {
        loadHorizontal();
        if(!directionKnown) loadVertical();
    }

};// 34911


class Day13 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;

    std::vector<Map> maps;
    
public:
    void loadMaps() {
        std::vector<std::vector<MapObject>> current;

        for(const std::string& line : input) {
            if(line.size() <= 1) {
                maps.push_back(Map(current));
                current = {};

                continue;
            }

            std::vector<MapObject> objects = {};
            for(const char& c : line) {
                objects.push_back((MapObject)c);
            }

            current.push_back(objects);
        }

        if(current.size() > 0) {
            maps.push_back(Map(current));
        }
    }

    void partA() {
        if(maps.size() <= 0) loadMaps();
        partASolution = 0;

        for(Map& map : maps) {
            if(map.isVertical()) partASolution += map.getVerticalMiddle() + 1;
            if(map.isHorizontal()) partASolution += (map.getHorizontalMiddle() + 1) * 100;
        }
    }

    void partB() {
        partBSolution = 0;
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day13() : Day("input/day13.txt") {}
};

#endif