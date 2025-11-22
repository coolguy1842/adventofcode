#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <chrono>
#include <string>

class Timer {
public:
    using clock = std::chrono::high_resolution_clock;

    using duration   = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<clock, duration>;

    Timer(std::string label);
    ~Timer() = default;

    void start();
    void stop();

    duration offset() const;

private:
    std::string m_label;

    time_point m_start;
    time_point m_stop;
};

#endif