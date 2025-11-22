#ifndef __IDAY_HPP__
#define __IDAY_HPP__

#include <Util/Timer.hpp>
#include <bitset>

class IDay {
public:
    enum SolutionFlags {
        A = 0,
        B = 1
    };

    IDay();
    virtual ~IDay() = default;

    void runParts(std::bitset<sizeof(SolutionFlags)> parts = (1 << A) | (1 << B));
    virtual void printSolutions(std::bitset<sizeof(SolutionFlags)> parts = (1 << A) | (1 << B)) = 0;

    const Timer& partATimer() const;
    const Timer& partBTimer() const;

protected:
    virtual void partA() = 0;
    virtual void partB() = 0;

    Timer m_partATimer;
    Timer m_partBTimer;
};

#endif