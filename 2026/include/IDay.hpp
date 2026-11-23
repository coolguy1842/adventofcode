#ifndef __IDAY_HPP__
#define __IDAY_HPP__

#include <Util/Timer.hpp>
#include <bitset>

class IDay {
public:
    enum PartIndexes : uint8_t {
        A = 0,
        B = 1
    };

    IDay();
    IDay(const IDay&)            = delete;
    IDay& operator=(const IDay&) = delete;

    virtual ~IDay() = default;

    void runParts(std::bitset<2> parts = (1 << A) | (1 << B));
    virtual void printSolutions(std::bitset<2> parts = (1 << A) | (1 << B)) = 0;

    [[nodiscard]] const Timer& partATimer() const;
    [[nodiscard]] const Timer& partBTimer() const;

protected:
    virtual void partA() = 0;
    virtual void partB() = 0;

    Timer m_partATimer;
    Timer m_partBTimer;
};

#endif