#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>

#include <cstddef>
#include <glm/ext/vector_int2.hpp>
#include <glm/glm.hpp>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    size_t aLightsOn, bLightsOn;

    size_t getNeighbours(bool* lights, const size_t& lightIndex, const size_t& width, const size_t& height, const bool& partB) {
        size_t indexRow = lightIndex / width;

        size_t neighbours = 0;
        for(long long y = -1; y <= 1; y++) {
            for(long long x = -1; x <= 1; x++) {
                if(x == 0 && y == 0) {
                    continue;
                }

                if(indexRow != (lightIndex + x) / width) {
                    continue;
                }
                
                size_t neighbourIndex = lightIndex + x + (y * height);
                // if it goes negative it will be > as unsigned so only need one case
                if(neighbourIndex >= width * height) {
                    continue;
                }
                
                if(partB && (
                    neighbourIndex == 0 ||
                    neighbourIndex == width - 1 ||
                    neighbourIndex == (width * height) - width ||
                    neighbourIndex == (width * height) - 1
                )) {
                    neighbours++;
                    continue;
                }

                neighbours += lights[neighbourIndex];
            }
        }

        return neighbours;
    }

    void runCycle(bool* lights, const size_t& width, const size_t& height, const bool& partB = false) {
        bool newState[width * height];
        memset(newState, false, width * height);

        for(size_t i = 0; i < width * height; i++) {
            size_t neighbours = getNeighbours(lights, i, width, height, partB);
            
            newState[i] = (lights[i] && neighbours == 2) || neighbours == 3;
        }

        memcpy(lights, newState, sizeof(newState));
    }


    // guaranteed to be a square
    size_t getDimensions() {
        const std::string& str = input.text;

        for(size_t i = 0; i < str.size(); i++) {
            if(str[i] == '\n') {
                return i;
            }
        }

        return str.size();
    }

    void initLights(bool* lights, const size_t& width, const size_t& height) {
        const std::string& str = input.text;

        size_t x = 0, y = 0;
        for(size_t i = 0; i < str.size(); i++) {
            switch(str[i]) {
            case '.': lights[(y * width) + x++] = false; break;
            case '#': lights[(y * width) + x++] = true; break;
            case '\n': x = 0; y++; break;
            default: break;
            }
        }
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aLightsOn(0), bLightsOn(0) {}

    void partA() {
        const std::string str = input.text;

        size_t width, height;
        width = height = getDimensions();

        bool lights[width * height];
        initLights(lights, width, height);

        for(size_t i = 0; i < 100; i++) {
            runCycle(lights, width, height);
        }

        for(size_t i = 0; i < width * height; i++) {
            aLightsOn += lights[i];
        }
    }

    void partB() {
        const std::string str = input.text;

        size_t width, height;
        width = height = getDimensions();

        bool lights[width * height];
        initLights(lights, width, height);

        for(size_t i = 0; i < 100; i++) {
            runCycle(lights, width, height, true);
        }

        // set all corner lights on since its only virtual with runcycle
        lights[0] = true;
        lights[width - 1] = true;
        lights[(width * height) - width] = true;
        lights[(width * height) - 1] = true;

        for(size_t i = 0; i < width * height; i++) {
            bLightsOn += lights[i];
        }
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aLightsOn);
        if(partB) spdlog::info("Part B: {}", bLightsOn);
    }
};

#endif