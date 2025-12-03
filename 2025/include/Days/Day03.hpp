#ifndef __DAY_3_HPP__
#define __DAY_3_HPP__

#include <include/IDay.hpp>

class Day3 : public IDay {
public:
    Day3()  = default;
    ~Day3() = default;

    void partA();
    void partB();

    void printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts = A | B);

private:
    uint64_t aSolution = 0;
    uint64_t bSolution = 0;
};

#endif