#include <Util/Timer.hpp>
#include <chrono>

Timer::Timer(std::string label)
    : m_label(label) {}

void Timer::start() {
    m_start = clock::now();
}

void Timer::stop() {
    m_stop = clock::now();
}

Timer::duration Timer::offset() const {
    if(m_start == clock::time_point() || m_stop == clock::time_point()) {
        printf("invalid\n");
        return duration();
    }

    return std::chrono::duration_cast<duration>(m_stop - m_start);
}