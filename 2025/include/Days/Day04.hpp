#ifndef __DAY_4_HPP__
#define __DAY_4_HPP__

#include <include/IDay.hpp>

class Day4 : public IDay {
public:
    Day4()  = default;
    ~Day4() = default;

    void partA();
    void partB();

    void printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts = A | B);

private:
    uint64_t aSolution = 0;
    uint64_t bSolution = 0;
};

#endif