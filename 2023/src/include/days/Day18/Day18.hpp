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

    std::vector<Coordinates> trenches;
    std::vector<Coordinates> trenchesB;

public:
    void loadInputA() {
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
        }
    }
   
    void loadInputB() {
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
        }
    }

    void partA() {
        if(trenches.size() <= 0) loadInputA();
        long long shoelace = 0;

        // Shoelace formula
        for (int i = 0; i < trenches.size(); i++) {
            Coordinates cur = trenches[i];
            Coordinates next = trenches[(i + 1) % trenches.size()];

            shoelace += (cur.y + next.y) * (cur.x - next.x);
        }
    
        // Pick's theorem
        partASolution = std::abs(shoelace / 2) + (trenches.size() / 2) + 1;
    }

    void partB() {
        if(trenchesB.size() <= 0) loadInputB();
        long long shoelace = 0;
        
        // Shoelace formula
        for (size_t i : range(trenchesB.size())) {
            const Coordinates& cur = trenchesB[i];
            const Coordinates& next = trenchesB[(i + 1) % trenchesB.size()];

            shoelace += (cur.y + next.y) * (cur.x - next.x);
        }
    
        // Pick's theorem
        partBSolution = std::abs(shoelace / 2) + (trenchesB.size() / 2) + 1;
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day18() : Day("input/day18.txt") {}
};

#endif