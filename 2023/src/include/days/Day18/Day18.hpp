#ifndef __DAY18_HPP__
#define __DAY18_HPP__

#include <util/helperStructs.hpp>

#include <day.hpp>
#include <stdio.h>

namespace partA {
enum Direction {
    UP    = 'U',
    DOWN  = 'D',
    LEFT  = 'L',
    RIGHT = 'R',
};
};

namespace partB {
enum Direction {
    RIGHT = '0',
    DOWN  = '1',
    LEFT  = '2',
    UP    = '3',
};
}


class Day18 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;

    enum SpaceType {
        TERRAIN = '.',
        TRENCH = '#'
    };

    long long maxXA, maxXB;
    long long minXA, minXB;

    long long maxYA, maxYB;
    long long minYA, minYB;

    std::vector<Coordinates> trenches;
    std::vector<Coordinates> trenchesB;

public:
    void loadInputA() {
        minXA = 0, minYA = 0;
        maxXA = 0, maxYA = 0;
        long long x = 0, y = 0;

        trenches.push_back(Coordinates(x, y));

        for(const std::string& line : input) {
            char direction;
            size_t toDig;

            sscanf(line.c_str(), "%c %zu", &direction, &toDig);

            do {
                switch(direction) {
                case partA::Direction::UP: y -= 1; break;
                case partA::Direction::DOWN : y += 1; break;
                case partA::Direction::LEFT: x -= 1; break;
                case partA::Direction::RIGHT: x += 1; break;
                }

                trenches.push_back(Coordinates(x, y));
            } while(--toDig);

            minXA = std::min(minXA, x);
            maxXA = std::max(maxXA, x + 1);

            minYA = std::min(minYA, y);
            maxYA = std::max(maxYA, y + 1);
        }
    }
   
    void loadInputB() {
        minXB = 0, minYB = 0;
        maxXB = 0, maxYB = 0;
        long long x = 0, y = 0;

        trenchesB.push_back(Coordinates(x, y));

        for(const std::string& line : input) {
            char direction;
            size_t toDig;

            sscanf(line.c_str(), "%*c %*zu (#%5x%c)", &toDig, &direction);

            do {
                switch(direction) {
                case partB::Direction::UP: y -= 1; break;
                case partB::Direction::DOWN : y += 1; break;
                case partB::Direction::LEFT: x -= 1; break;
                case partB::Direction::RIGHT: x += 1; break;
                }

                trenchesB.push_back(Coordinates(x, y));
            } while(--toDig);

            minXB = std::min(minXB, x);
            maxXB = std::max(maxXB, x + 1);

            minYB = std::min(minYB, y);
            maxYB = std::max(maxYB, y + 1);
        }
    }


    bool inBounds(const std::vector<Coordinates>& bounds, const Coordinates& position) {
        size_t j = bounds.size() - 1;
        bool ret = false;

        for(size_t i = 0; i < bounds.size(); i++) {
            if (position == bounds[i]) return true;

            if ((bounds[i].y > position.y) != (bounds[j].y > position.y)) {
                long slope = (position.x - bounds[i].x) * (bounds[j].y - bounds[i].y) - (bounds[j].x - bounds[i].x) * (position.y - bounds[i].y);

                if(slope == 0) return true;
                if((slope < 0) != (bounds[j].y < bounds[i].y)) ret = !ret;
            }

            j = i;
        }

        return ret;
    }

    void partA() {
        if(trenches.size() <= 0) loadInputA();
        partASolution = 0;

        for(const long long& y : range(minYA, maxYA)) {
            for(const long long& x : range(minXA, maxXA)) {
                if(!inBounds(trenches, Coordinates(x, y))) continue;
                partASolution++;
            }
        }
    }

    void partB() {
        if(trenchesB.size() <= 0) loadInputB();
        partBSolution = 0;

        for(const long long& y : range(minYB, maxYB)) {
            for(const long long& x : range(minXB, maxXB)) {
                if(!inBounds(trenchesB, Coordinates(x, y))) continue;
                partBSolution++;
            }
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day18() : Day("input/day18.txt") {}
};

#endif