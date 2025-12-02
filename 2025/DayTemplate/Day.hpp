#ifndef __DAY_N_HPP__
#define __DAY_N_HPP__

#include <include/IDay.hpp>

class DayN : public IDay {
public:
    DayN()  = default;
    ~DayN() = default;

    void partA();
    void partB();

    void printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts = A | B);

private:
    uint64_t aSolution = 0;
    uint64_t bSolution = 0;
};

#endif