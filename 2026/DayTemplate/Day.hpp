#ifndef __DAY_N_HPP__
#define __DAY_N_HPP__

#include <include/IDay.hpp>

class DayN : public IDay {
public:
    void partA() final;
    void partB() final;

    void printSolutions(std::bitset<2> parts = A | B) final;

private:
    uint64_t aSolution = 0;
    uint64_t bSolution = 0;
};

#endif