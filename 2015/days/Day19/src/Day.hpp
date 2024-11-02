#ifndef __DAY_HPP__
#define __DAY_HPP__

#include "scn/scan.h"
#include <IDay.hpp>
#include <cstdio>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_set>
#include <vector>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

struct Replacement {
    std::string original;
    std::string result;
};

class Day : public AOCUtil::IDay {
private:
    size_t aMoleculeCount;

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aMoleculeCount(0) {}

    void partA() {
        std::unordered_set<std::string> molecules;

        // original, replacement
        std::vector<Replacement> replacements;
        std::string sequence;

        std::vector<std::string>& splitLines = input.getSplitText("\n");
        for(size_t i = 0; i < splitLines.size() - 2; i++) {
            std::string& line = splitLines[i];

            auto result = scn::scan<std::string, std::string>(line, "{} => {}");
            auto [ original, replacement ] = result->values();

            replacements.push_back({
                original,
                replacement
            });
        }

        sequence = splitLines[splitLines.size() - 1];

        for(const Replacement& replacement : replacements) {            
            while(true) {
                std::string copy = sequence;
                
            }
        }
    }

    void partB() { }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aMoleculeCount);
    }
};

#endif