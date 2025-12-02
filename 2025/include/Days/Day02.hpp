#ifndef __DAY_2_HPP__
#define __DAY_2_HPP__

#include <include/IDay.hpp>

class Day2 : public IDay {
public:
    Day2()  = default;
    ~Day2() = default;

    void partA();
    void partB();

    void printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts = A | B);

private:
    uint64_t aSolution = 0;
    uint64_t bSolution = 0;
};

#endif