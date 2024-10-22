#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <spdlog/spdlog.h>

#include <chrono>
#include <optional>

namespace AOCUtil {

enum DurationLevel {
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECONDS
};

class Timer {
private:
    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<std::chrono::high_resolution_clock, duration>;
    
    std::optional<time_point> _start;
    std::optional<time_point> _stop;

public:
    void start();
    std::optional<duration> stop();

    std::optional<duration> get_last();
    void print(DurationLevel level = DurationLevel::MILLISECONDS);
};

};

#endif