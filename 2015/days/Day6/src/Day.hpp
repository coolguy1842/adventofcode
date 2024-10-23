#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <cstdlib>
#include <utils/Range.hpp>

#include <scn/scan.h>
#include <scn/regex.h>
#include <IDay.hpp>
#include <cstdio>
#include <cstring>
#include <glm/ext/vector_int2.hpp>
#include <spdlog/spdlog.h>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

#define GRID_SIZE 1000
#define GRID_INIT_VALUE 0

class Day : public AOCUtil::IDay {
private:
    size_t lit;
    size_t brightness;

    int coordsToIndex(int x, int y) {
        return (y * GRID_SIZE) + x;
    }

    glm::ivec2 indexToCoords(int index) {
        return glm::ivec2(
            index % GRID_SIZE,
            index / GRID_SIZE
        );
    }

    enum GridCommand {
        ON,
        TOGGLE,
        OFF
    };

    void runGridCommand(int grid[GRID_SIZE * GRID_SIZE], AOCUtil::Range<int> xRange, AOCUtil::Range<int> yRange, GridCommand command, bool partB = false) {
        switch(command) {
        case GridCommand::ON:
            for(int x : xRange) {
                for(int y : yRange) {
                    int i = coordsToIndex(x, y);

                    if(!partB) {
                        grid[i] = true;
                    }
                    else {
                        grid[i]++;
                    }
                }    
            }

            break;
        case GridCommand::OFF:
            for(int x : xRange) {
                for(int y : yRange) {
                    int i = coordsToIndex(x, y);
                    
                    if(!partB) {
                        grid[i] = false;
                    }
                    else {
                        grid[i] = std::max(0, grid[i] - 1);
                    }
                }    
            }

            break;
        case GridCommand::TOGGLE:
            for(int x : xRange) {
                for(int y : yRange) {
                    int i = coordsToIndex(x, y);
                                        
                    if(!partB) {
                        grid[i] = !grid[i];
                    }
                    else {
                        grid[i] += 2;
                    }
                }    
            }

            break;
        default: break;
        }
    }


    size_t partFunc(bool partB = false) {
        int grid[GRID_SIZE * GRID_SIZE];
        memset(grid, GRID_INIT_VALUE, sizeof(grid));

        for(std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<std::string, int, int, int, int>(line, "{:[^0-9]} {},{} through {},{}");
            auto [ command, rangeXStart, rangeYStart, rangeXEnd, rangeYEnd ] = result->values();

            GridCommand gridCommand;
            // t*u*rn
            if(command[1] == 'u') {
                // o*n*
                if(command[6] == 'n') {
                    gridCommand = GridCommand::ON;
                }
                else {
                    gridCommand = GridCommand::OFF;    
                }
            }
            else {
                gridCommand = GridCommand::TOGGLE;
            }

            runGridCommand(grid, AOCUtil::Range(rangeXStart, rangeXEnd + 1), AOCUtil::Range(rangeYStart, rangeYEnd + 1), gridCommand, partB);
        }

        size_t out = 0;
        for(int& light : grid) {
            out += light;
        }

        return out;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), lit(0), brightness(0) {}

    void partA() {
        lit = partFunc();
    }

    void partB() {
        brightness = partFunc(true);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", lit);
        if(partB) spdlog::info("Part B: {}", brightness);
    }
};

#endif