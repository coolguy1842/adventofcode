#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>
#include <spdlog/spdlog.h>

class Day : public AOCUtil::IDay {
private:

public:
    Day() : AOCUtil::IDay(INPUT_PATH) {}

    void partA() { }
    void partB() { }

    void printResults(bool partA, bool partB) {

    }
};

#endif