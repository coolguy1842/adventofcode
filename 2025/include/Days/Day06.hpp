#ifndef __DAY_6_HPP__
#define __DAY_6_HPP__

#include <include/IDay.hpp>

class Day6 : public IDay {
public:
    Day6()  = default;
    ~Day6() = default;

    void partA();
    void partB();

    void printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts = A | B);

private:
    uint64_t aSolution = 0;
    uint64_t bSolution = 0;
};

#endif