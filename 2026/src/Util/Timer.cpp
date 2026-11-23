#include <Util/Timer.hpp>
#include <chrono>
#include <spdlog/spdlog.h>

Timer::Timer(std::string label)
    : m_label(std::move(label)) {}

void Timer::start() {
    m_start = clock::now();
}

void Timer::stop() {
    m_stop = clock::now();
}

Timer::duration Timer::offset() const {
    if(m_start == clock::time_point() || m_stop == clock::time_point()) {
        spdlog::warn("invalid timer state");
        return {};
    }

    return std::chrono::duration_cast<duration>(m_stop - m_start);
}