#ifndef __DAY_5_HPP__
#define __DAY_5_HPP__

#include <include/IDay.hpp>

class Day5 : public IDay {
public:
    Day5()  = default;
    ~Day5() = default;

    void partA();
    void partB();

    void printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts = A | B);

private:
    uint64_t aSolution = 0;
    uint64_t bSolution = 0;
};

#endif