#include <IDay.hpp>

IDay::IDay()
    : m_partATimer("Part A")
    , m_partBTimer("Part B") {}

void IDay::runParts(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        m_partATimer.start();
        partA();
        m_partATimer.stop();
    }

    if(parts.test(B)) {
        m_partBTimer.start();
        partB();
        m_partBTimer.stop();
    }
}

const Timer& IDay::partATimer() const { return m_partATimer; }
const Timer& IDay::partBTimer() const { return m_partBTimer; }