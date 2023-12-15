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
    bool vertical = false, directionKnown = false;
    bool verticalB = false, directionKnownB = false;
    
    long long verticalMiddle, horizontalMiddle;
    long long verticalMiddleB, horizontalMiddleB;

    std::vector<MapObject> verticalObject(size_t i) {
        std::vector<MapObject> out;
        
        for(size_t j : range(rows.size())) {
            out.push_back(rows[j][i]);
        }

        return out;
    }

    // both strings are assumed to be the same length
    size_t objDifferences(std::vector<MapObject> a, std::vector<MapObject> b) {
        size_t differences = 0;

        for(size_t i = 0; i < a.size(); i++) {
            if(a[i] != b[i]) differences++;
        }

        return differences;
    }


    void loadHorizontal(bool partB = false) {
        for(long long i = (long long)rows.size() - 2; i >= 0; i--) {
            if(partB && (!vertical && horizontalMiddle == i)) continue;
            size_t differences = 0;
           
            long long left, right;
            for(left = i, right = i + 1; left >= 0 && right < (long long)rows.size(); left--, right++) {
                differences += objDifferences(rows[left], rows[right]);

                if(differences > partB) {
                    break;
                }
            }

            if((left <= 0 || right >= (long long)rows.size() - 1) && differences == partB) {
                if(!partB) {
                    vertical = false;
                    directionKnown = true;

                    horizontalMiddle = i;
                }
                else {
                    verticalB = false;
                    directionKnownB = true;

                    horizontalMiddleB = i;
                }
                
                return;
            }
        }
    }
    
    void loadVertical(bool partB = false) {
        for(long long i = (long long)rows[0].size() - 2; i >= 0; i--) {
            if(partB && (vertical && verticalMiddle == i)) continue;
            size_t differences = 0;
           
            long long left, right;
            for(left = i, right = i + 1; left >= 0 && right < (long long)rows[0].size(); left--, right++) {
                differences += objDifferences(verticalObject(left), verticalObject(right));

                if(differences > partB) {
                    break;
                }
            }

            if((left <= 0 || right >= (long long)rows[0].size() - 1) && differences == partB) {
                if(!partB) {
                    vertical = true;
                    directionKnown = true;

                    verticalMiddle = i;
                }
                else {
                    verticalB = true;
                    directionKnownB = true;

                    verticalMiddleB = i;
                }
                
                return;
            }
        }
    }

public:
    std::vector<std::vector<MapObject>> getRows() { return rows; }

    bool isVertical(bool partB = false) const { return partB ? verticalB : vertical; }
    bool isHorizontal(bool partB = false) const { return partB ? !verticalB : !vertical; }
    
    long long getVerticalMiddle() const { return verticalMiddle; }
    long long getHorizontalMiddle() const { return horizontalMiddle; }
    
    long long getVerticalMiddleB() const { return verticalMiddleB; }
    long long getHorizontalMiddleB() const { return horizontalMiddleB; }

    Map(std::vector<std::vector<MapObject>> rows) : rows(rows) {
        loadHorizontal(false);
        if(!directionKnown) loadVertical(false);

        loadHorizontal(true);
        if(!directionKnownB) loadVertical(true);
    }
};


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
        if(maps.size() <= 0) loadMaps();
        partBSolution = 0;

        for(Map& map : maps) {
            if(map.isVertical(true)) partBSolution += map.getVerticalMiddleB() + 1;
            if(map.isHorizontal(true)) partBSolution += (map.getHorizontalMiddleB() + 1) * 100;
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day13() : Day("input/day13.txt") {}
};

#endif