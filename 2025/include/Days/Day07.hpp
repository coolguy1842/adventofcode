#ifndef __DAY_7_HPP__
#define __DAY_7_HPP__

#include <include/IDay.hpp>

class Day7 : public IDay {
public:
    Day7()  = default;
    ~Day7() = default;

    void partA();
    void partB();

    void printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts = A | B);

private:
    uint64_t aSolution = 0;
    uint64_t bSolution = 0;
};

#endif