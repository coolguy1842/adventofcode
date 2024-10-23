#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <utils/Range.hpp>

#include <glm/ext/vector_int2.hpp>
#include <spdlog/spdlog.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <IDay.hpp>

#include <glm/glm.hpp>
#include <unordered_set>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    size_t aUniqueHouses;
    size_t bUniqueHouses;
    
    size_t loopFunc(bool partB) {
        std::unordered_set<glm::ivec2> positions;
        glm::ivec2 position(0), roboPosition(0);

        positions.emplace(position);
        for(size_t i : AOCUtil::Range(input.text.size())) {
            bool human = !partB || i % 2 == 0;
            switch(input.text[i]) {
            case '>': (human ? position.x : roboPosition.x)++; break;
            case '<': (human ? position.x : roboPosition.x)--; break;
            case '^': (human ? position.y : roboPosition.y)++; break;
            case 'v': (human ? position.y : roboPosition.y)--; break;
            default: break;
            }

            positions.emplace(human ? position : roboPosition);
        }

        return positions.size();
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aUniqueHouses(0), bUniqueHouses(0) {}

    void partA() {
        aUniqueHouses = loopFunc(false);
    }

    void partB() {
        bUniqueHouses = loopFunc(true);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aUniqueHouses);
        if(partB) spdlog::info("Part B: {}", bUniqueHouses);
    }
};

#endif