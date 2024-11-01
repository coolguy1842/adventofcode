#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>

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

    static glm::ivec2 indexToCoords(const size_t& index, const size_t& width) {
        return glm::ivec2(index % width, index / width);
    }

    static size_t coordsToIndex(const size_t& x, const size_t& y, const size_t& width) {
        return (y * width) + x;
    }


    static void printLights(bool* lights, const size_t& width, const size_t& height) {
        for(size_t y = 0; y < height; y++) {
            for(size_t x = 0; x < width; x++) {
                printf("%c", lights[(y * width) + x] ? '#' : '.');
            }
            
            printf("\n");
        }
    }

    size_t getNeighbours(bool* lights, const size_t& lightIndex, const size_t& width, const size_t& height, const bool& partB) {
        glm::ivec2 coords = indexToCoords(lightIndex, width);

        size_t neighbours = 0;
        for(size_t i = 0; i < 9; i++) {
            glm::ivec2 neighbourCoords;

            neighbourCoords.x = coords.x + ((i % 3) - 1);
            if(neighbourCoords.x < 0 || neighbourCoords.x >= width) {
                continue;
            }

            neighbourCoords.y = coords.y + ((i / 3) - 1);
            if(neighbourCoords.y < 0 || neighbourCoords.y >= height) {
                continue;
            }

            if(neighbourCoords.x == coords.x && neighbourCoords.y == coords.y) {
                continue;
            }
            else if(partB && ((neighbourCoords.x == 0 || neighbourCoords.x == width - 1) && (neighbourCoords.y == 0 || neighbourCoords.y == height - 1))) {
                neighbours++;
                continue;
            }

            size_t neighbourIndex = coordsToIndex(neighbourCoords.x, neighbourCoords.y, width);
            neighbours += lights[neighbourIndex];
        }

        return neighbours;
    }

    void runCycle(bool* lights, const size_t& width, const size_t& height, const bool& partB = false) {
        bool newState[width * height];
        memset(newState, false, width * height);

        for(size_t i = 0; i < width * height; i++) {
            size_t neighbours = getNeighbours(lights, i, width, height, partB);
            
            if(lights[i]) {
                newState[i] = neighbours == 2 || neighbours == 3;
            }
            else {
                newState[i] = neighbours == 3;
            }
        }

        memcpy(lights, newState, sizeof(newState));
    }


    void getDimensions(size_t& width, size_t& height) {
        const std::string& str = input.text;

        width = 0, height = 1;
        for(size_t i = 0; i < str.size(); i++) {
            switch(str[i]) {
            case '\n':
                if(width == 0) width = i;
                height++;
            default: break;
            }
        }
    }

    void initLights(bool* lights, const size_t& width, const size_t& height) {
        const std::string& str = input.text;

        size_t x = 0, y = 0;
        for(size_t i = 0; i < str.size(); i++) {
            switch(str[i]) {
            case '.': lights[coordsToIndex(x++, y, width)] = false; break;
            case '#': lights[coordsToIndex(x++, y, width)] = true; break;
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
        getDimensions(width, height);

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
        getDimensions(width, height);

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