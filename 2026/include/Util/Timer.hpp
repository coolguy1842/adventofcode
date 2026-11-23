#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <chrono>
#include <string>

class Timer {
public:
    using clock = std::chrono::high_resolution_clock;

    using duration   = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<clock, duration>;

    explicit Timer(std::string label);
    Timer(const Timer&)            = delete;
    Timer& operator=(const Timer&) = delete;

    ~Timer() = default;

    void start();
    void stop();

    [[nodiscard]] duration offset() const;

private:
    const std::string m_label;

    time_point m_start;
    time_point m_stop;
};

#endif