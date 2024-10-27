#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>
#include <spdlog/spdlog.h>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    size_t aSolution;
    size_t bSolution;

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aSolution(0), bSolution(0) {}

    void partA() {
        for(std::string& line : input.getSplitText("\n")) {
            size_t codeSize = line.size();
            size_t memorySize = 0;

            for(size_t i = 1; i < line.size() - 1; i++) {
                const char& c = line[i];
                
                switch(c) {
                case '\\':
                    switch(line[i + 1]) {
                    case 'x':
                        i += 3;
                        break;
                    default:
                        i++;
                        break;
                    }

                    break;
                default: break;
                }

                memorySize++;
            }

            aSolution += codeSize - memorySize;
        }
    }

    void partB() {
        for(std::string& line : input.getSplitText("\n")) {
            size_t codeSize = line.size();
            // min size
            size_t memorySize = 6;

            for(size_t i = 1; i < line.size() - 1; i++) {
                const char& c = line[i];
                
                switch(c) {
                case '\\':
                case '"':
                    memorySize += 2;
                    break;
                default: 
                    memorySize++;
                    break;
                }
            }

            bSolution += memorySize - codeSize;
        }
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aSolution);
        if(partB) spdlog::info("Part B: {}", bSolution);
    }
};

#endif