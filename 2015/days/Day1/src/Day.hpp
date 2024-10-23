#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>
#include <optional>
#include <spdlog/spdlog.h>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    long long floor;
    std::optional<size_t> basementStart;

    void loopFunc(bool partB) {
        for(size_t i = 0; i < input.text.size(); i++) {
            switch(input.text[i]) {
            case '(': floor++; break;
            case ')': floor--; break;
            default: break;
            }

            if(!basementStart.has_value() && floor < 0) {
                basementStart = i + 1;

                if(partB) {
                    return;
                }
            }
        }
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), floor(0), basementStart(std::nullopt) {}

    void partA() {
        loopFunc(false);
    }

    void partB() {
        if(basementStart.has_value()) return;
        loopFunc(true);
    }


    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", floor);
        if(partB) {
            if(basementStart.has_value()) {
                spdlog::info("Part B: {}", basementStart.value());
            }
            else {
                spdlog::info("Part B: No Basement Found");
            }
        }
    }
};

#endif