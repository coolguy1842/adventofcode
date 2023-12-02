#ifndef __DAY2_HPP__
#define __DAY2_HPP__

#include <spdlog/spdlog.h>
#include <day.hpp>

#include <vector>

enum Colour {
    RED = 'r',
    GREEN = 'g',
    BLUE = 'b'
};

struct Cube {
    Colour colour;
    int count;
};

struct Set {
    std::vector<Cube> cubes;
};

struct Game {
    int id;
    std::vector<Set> sets;
};

class Day2 : public AOC::Day {
private:
    int partASolution;
    int partBSolution;

    std::vector<Game> games;

public:
    void getGames() {
        for(std::string& line : input) {
            std::vector<std::string> splitStr = split(line, ": ");
            
            Game game;
            game.id = atoi(splitStr[0].c_str() + 5);

            for(std::string& setStr : split(splitStr[1], "; ")) {
                Set set;

                for(std::string& cubeStr : split(setStr, ", ")) {
                    std::vector<std::string> info = split(cubeStr, " ");
                    
                    Cube cube = { (Colour)info[1][0], atoi(info[0].c_str()) };
                    set.cubes.push_back(cube);
                }

                game.sets.push_back(set);
            }

            games.push_back(game);
        }
    }


    void partA() {
        if(games.size() <= 0) this->getGames();
        
        const int maxRed = 12;
        const int maxGreen = 13;
        const int maxBlue = 14;

        partASolution = 0;

        for(Game& game : games) {
            for(Set& set : game.sets) {
                for(Cube& cube : set.cubes) {
                    switch(cube.colour) {
                    case Colour::RED: if(cube.count > maxRed) goto skip; break;
                    case Colour::GREEN: if(cube.count > maxGreen) goto skip; break;
                    case Colour::BLUE: if(cube.count > maxBlue) goto skip; break;
                    default: break;
                    }
                }
            }

            partASolution += game.id;
            skip:
        }
    }
    
    void partB() {
        if(games.size() <= 0) this->getGames();
        partBSolution = 0;

        for(Game& game : games) {
            int maxRedUsed = 0, maxBlueUsed = 0, maxGreenUsed = 0;
            
            for(Set& set : game.sets) {
                for(Cube& cube : set.cubes) {
                    switch(cube.colour) {
                    case Colour::RED: maxRedUsed = std::max(maxRedUsed, cube.count); break;
                    case Colour::GREEN: maxBlueUsed = std::max(maxBlueUsed, cube.count); break;
                    case Colour::BLUE: maxGreenUsed = std::max(maxGreenUsed, cube.count); break;
                    default: break;
                    }
                }    
            }
            
            partBSolution += maxRedUsed * maxGreenUsed * maxBlueUsed;
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) spdlog::info("partA: {}", partASolution);
        if(partB) spdlog::info("partB: {}", partBSolution);
    }

    Day2() : Day("input/day2.txt") {}
};

#endif