#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <algorithm>
#include <numeric>
#include <scn/scan.h>

#include <IDay.hpp>
#include <spdlog/spdlog.h>
#include <string>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    size_t paperAmount;
    size_t ribbonAmount;

public:
    Day() : AOCUtil::IDay(INPUT_PATH), paperAmount(0), ribbonAmount(0) {}

    void partA() {
        for(std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<int, int, int>(line, "{}x{}x{}");
            auto [ length, width, height ] = result->values();

            int sides[] = {
                length * width,
                width * height,
                height * length
            };

            int* end = sides + (sizeof(sides) / sizeof(int));
            int slack = *std::min_element(sides, end);

            paperAmount += (std::accumulate(sides, end, 0) * 2) + slack;
        }
    }

    void partB() {
        for(std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<int, int, int>(line, "{}x{}x{}");
            auto [ length, width, height ] = result->values();

            int sides[] = {
                length * 2 + width * 2,
                width * 2 + height * 2,
                height * 2 + length * 2
            };

            int* end = sides + (sizeof(sides) / sizeof(int));
            int side = *std::min_element(sides, end);

            ribbonAmount += side + (length * width * height);
        }
    }


    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", paperAmount);
        if(partA) spdlog::info("Part B: {}", ribbonAmount);
    }
};

#endif