#ifndef __DAY_1_HPP__
#define __DAY_1_HPP__

#include <include/IDay.hpp>

class Day1 : public IDay {
public:
    Day1()  = default;
    ~Day1() = default;

    void partA();
    void partB();

    void printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts = A | B);

private:
    int32_t aSolution = 0;
    int32_t bSolution = 0;
};

#endif