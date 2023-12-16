#ifndef __DAY16_HPP__
#define __DAY16_HPP__

#include <util/helperStructs.hpp>

#include <day.hpp>
#include <stdio.h>

#include <chrono>

struct Light {
    enum Direction {
        NORTH = 0,
        SOUTH,
        EAST,
        WEST,
    };

    Coordinates coords;
    Direction direction;

    bool operator==(const Light& other) {
        return coords == other.coords && direction == other.direction;
    }
};

bool operator==(const Light& a, const Light& b) {
    return a.coords == b.coords && a.direction == b.direction;
}

struct light_hash {
    inline std::size_t operator()(const Light& c) const {
        return ((size_t)c.coords.x << 32) + ((size_t)c.coords.y << 16) + c.direction;
    }
};


class Map {
private:
    void stepLight(Light& light) {
        switch(grid[light.coords.y][light.coords.x]) {
        case Object::VERTICALSPLITTER: {
            if(light.direction == Light::Direction::NORTH || light.direction == Light::Direction::SOUTH) break;

            light.direction = Light::Direction::NORTH;

            Light newLight = { light.coords, Light::Direction::SOUTH };
            if(!travelled.contains(newLight)) lights.push_back(newLight);

            break;
        }
        case Object::HORIZONTALSPLITTER: {
            if(light.direction == Light::Direction::EAST || light.direction == Light::Direction::WEST) break;

            light.direction = Light::Direction::EAST;

            Light newLight = { light.coords, Light::Direction::WEST };
            if(!travelled.contains(newLight)) lights.push_back(newLight);

            break;
        }
        case Object::LEFTMIRROR: {
            switch(light.direction) {
            case Light::Direction::WEST: light.direction = Light::Direction::SOUTH; break;
            case Light::Direction::SOUTH: light.direction = Light::Direction::WEST; break;
            case Light::Direction::EAST: light.direction = Light::Direction::NORTH; break;
            case Light::Direction::NORTH: light.direction = Light::Direction::EAST; break;
            default: break;
            }

            break;
        }
        case Object::RIGHTMIRROR: {
            switch(light.direction) {
            case Light::Direction::WEST: light.direction = Light::Direction::NORTH; break;
            case Light::Direction::NORTH: light.direction = Light::Direction::WEST; break;
            case Light::Direction::EAST: light.direction = Light::Direction::SOUTH; break;
            case Light::Direction::SOUTH: light.direction = Light::Direction::EAST; break;
            default: break;
            }

            break;
        }
        default: break;
        }

        switch(light.direction) {
        case Light::Direction::NORTH: light.coords.y--; break;
        case Light::Direction::SOUTH: light.coords.y++; break;
        case Light::Direction::EAST:  light.coords.x++; break;
        case Light::Direction::WEST:  light.coords.x--; break;
        default: break;
        }
    }
    
public:
    enum Object {
        LEFTMIRROR = '/',
        RIGHTMIRROR = '\\',
        HORIZONTALSPLITTER = '-',
        VERTICALSPLITTER = '|',
        EMPTY = '.'
    };


    std::vector<std::string> grid;

    robin_hood::unordered_flat_set<Coordinates, coordinates_hash> charged;
    robin_hood::unordered_flat_set<Light, light_hash> travelled;
    
    std::vector<Light> lights;

    bool step() {
        for(auto it = lights.begin(); it != lights.end();) {
            Light& light = *it;

            if(travelled.contains({ light.coords, light.direction })) {
                it = lights.erase(it);
                continue;
            }


            charged.emplace(light.coords);
            travelled.emplace(Light { light.coords, light.direction });
            stepLight(light);

            if(light.coords.x < 0 || light.coords.x >= (long long)grid[0].size() || light.coords.y < 0 || light.coords.y >= (long long)grid.size()) {
                it = lights.erase(it);
                continue;
            }
            
            it++;
        }

        return lights.size();
    }
};

class Day16 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    Map mapA;
    Map mapB;

public:
    void loadMap() {
        mapA.grid = input;
        mapB.grid = input;

        // to stop the reference from getting destroyed
        mapA.lights.reserve(1000000);
        mapB.lights.reserve(1000000);
    }

    void partA() {
        if(mapA.grid.size() <= 0) loadMap();
        partASolution = 0;

        mapA.lights.push_back({ Coordinates{0, 0}, Light::Direction::EAST });
        while(mapA.step());

        partASolution = mapA.charged.size();
    }

    void partB() {
        if(mapB.grid.size() <= 0) loadMap();
        partBSolution = 0;

        for(size_t y = 0; y < mapB.grid.size(); y++) {
            for(size_t x = 0; x < mapB.grid[0].size(); x++) {
                if(x > 0 && x < mapB.grid[0].size() - 1 && y > 0 && y < mapB.grid.size() - 1) continue;
                if(mapB.grid[y][x] != Map::Object::EMPTY) continue;

                std::vector<Light::Direction> directions;
                if(y == 0) directions.push_back(Light::Direction::SOUTH);
                else if(y > 0) directions.push_back(Light::Direction::NORTH);

                if(x == 0) directions.push_back(Light::Direction::EAST);
                else if(x > 0) directions.push_back(Light::Direction::WEST);

                for(const Light::Direction& dir : directions) {
                    mapB.travelled = {};
                    mapB.charged = {};

                    mapB.lights.push_back({ Coordinates(x, y), dir });
                    while(mapB.step());
                    
                    partBSolution = std::max(partBSolution, mapB.charged.size());
                }
            }
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day16() : Day("input/day16.txt") {}
};

#endif