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

    size_t getNeighbours(bool* lights, const size_t& lightIndex, const size_t& resolution, const size_t& arraySize, const bool& partB) {
        size_t indexRow = lightIndex / resolution, neighbours = 0;
        for(long long y = -resolution; y <= (long long)resolution; y += resolution) {
            for(long long x = -1; x <= 1; x++) {
                // if the neighbours x is not on the same row then continue
                if((!x && !y) || (indexRow != (lightIndex + x) / resolution)) {
                    continue;
                }
                
                size_t neighbourIndex = lightIndex + x + y;
                // if it goes negative it will be > as unsigned so only need one case
                if(neighbourIndex >= arraySize) {
                    continue;
                }
                
                if(partB && (
                    neighbourIndex == 0 ||
                    neighbourIndex == resolution - 1 ||
                    neighbourIndex == arraySize - resolution ||
                    neighbourIndex == arraySize - 1
                )) {
                    neighbours++;
                    continue;
                }

                neighbours += lights[neighbourIndex];
            }
        }

        return neighbours;
    }

    void runCycle(bool* lights, const size_t& resolution, const size_t& arraySize, const bool& partB = false) {
        bool newState[arraySize];
        for(size_t i = 0; i < arraySize; i++) {
            size_t neighbours = getNeighbours(lights, i, resolution, arraySize, partB);
            
            newState[i] = neighbours == 3 || (lights[i] && neighbours == 2);
        }

        memcpy(lights, newState, sizeof(newState));
    }


    // guaranteed to be a square so only need to get one resolution
    size_t getDimensions() {
        const char* strStart = input.text.c_str(), *cur = strStart;

        while(*cur++ != '\n');
        return (cur - 1) - strStart;
    }

    void initLights(bool* lights) {
        const char* str = input.text.c_str();

        while(true) {
            switch(*str++) {
            case '.': *lights++ = false; break;
            case '#': *lights++ = true; break;
            case '\0': return;
            default: break;
            }
        }
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aLightsOn(0), bLightsOn(0) {}

    void partA() {
        size_t resolution = getDimensions(), arraySize = resolution * resolution;
        bool lights[arraySize];
        
        initLights(lights);

        for(size_t i = 0; i < 100; i++) {
            runCycle(lights, resolution, arraySize);
        }

        for(size_t i = 0; i < arraySize; i++) {
            aLightsOn += lights[i];
        }
    }

    void partB() {
        size_t resolution = getDimensions(), arraySize = resolution * resolution;
        bool lights[arraySize];

        initLights(lights);

        for(size_t i = 0; i < 100; i++) {
            runCycle(lights, resolution, arraySize, true);
        }

        // set all corner lights on since its only virtual with runcycle
        lights[0] = true;
        lights[resolution - 1] = true;
        lights[arraySize - resolution] = true;
        lights[arraySize - 1] = true;

        for(size_t i = 0; i < arraySize; i++) {
            bLightsOn += lights[i];
        }
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aLightsOn);
        if(partB) spdlog::info("Part B: {}", bLightsOn);
    }
};

#endif