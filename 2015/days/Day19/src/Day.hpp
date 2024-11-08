#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <algorithm>
#include <scn/scan.h>
#include <IDay.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
    std::string replacement;
};

class Day : public AOCUtil::IDay {
private:
    size_t aMoleculeCount;
    size_t bMoleculeSteps;

    std::vector<Replacement> initReplacements(const std::vector<std::string>& splitLines) {
        std::vector<Replacement> out;

        for(size_t i = 0; i < splitLines.size() - 2; i++) {
            const std::string& line = splitLines[i];

            auto result = scn::scan<std::string, std::string>(line, "{} => {}");
            auto [ original, replacement ] = result->values();

            out.push_back({
                original,
                replacement
            });
        }

        return out;
    }

    inline bool matchStrings(const char* first, const char* second) {
        while(*second != '\0') {
            if(*first++ != *second++) {
                return false;
            }
        }

        return true;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aMoleculeCount(0), bMoleculeSteps(0) {}

    void partA() {
        std::vector<std::string>& splitLines = input.getSplitText("\n");
        std::vector<Replacement> replacements = initReplacements(splitLines);
        
        std::unordered_set<std::string> molecules;
        const std::string& molecule = splitLines[splitLines.size() - 1];

        for(const Replacement& replacement : replacements) {
            for(size_t i = 0; i < molecule.size(); i++) {
                if(matchStrings(molecule.c_str() + i, replacement.original.c_str())) {
                    molecules.emplace(molecule.substr(0, i) + replacement.replacement + molecule.substr(i + replacement.original.size()));
                }
            }
        }

        aMoleculeCount = molecules.size();
    }

    void partB() {
        std::vector<std::string>& splitLines = input.getSplitText("\n");
        std::vector<Replacement> replacements = initReplacements(splitLines);

        // reversing all the strings is faster
        for(Replacement& replacement : replacements) {
            std::reverse(replacement.original.begin(), replacement.original.end());
            std::reverse(replacement.replacement.begin(), replacement.replacement.end());
        }
        
        std::string cur = splitLines[splitLines.size() - 1];
        std::reverse(cur.begin(), cur.end());

        while(cur != "e") {
            for(size_t i = 0; i < cur.size(); i++) {
                for(const Replacement& replacement : replacements) {
                    if(matchStrings(cur.c_str() + i, replacement.replacement.c_str())) {
                        cur = cur.substr(0, i) + replacement.original + cur.substr(i + replacement.replacement.size());
                        bMoleculeSteps++;

                        break;
                    }
                }
            }
        }
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aMoleculeCount);
        if(partB) spdlog::info("Part B: {}", bMoleculeSteps);
    }
};

#endif