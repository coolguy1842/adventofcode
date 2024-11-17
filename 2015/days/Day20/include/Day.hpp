#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    size_t aHouseNumber;
    size_t bHouseNumber;

    size_t getHouse(size_t* houses, const size_t& numHouses, const size_t& findAmount, const size_t& elfDeliverCount, const size_t& elfDeliverMultiplier);

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aHouseNumber(0), bHouseNumber(0) {}

    void partA();
    void partB();

    void printResults(bool partA, bool partB);
};

#endif