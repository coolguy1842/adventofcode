#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <spdlog/spdlog.h>

#include <chrono>
#include <optional>
#include <string>

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

    std::string _name;

public:
    Timer() : _name("") {}
    Timer(std::string name) : _name(name) {}

    virtual void start();
    virtual std::optional<duration> stop();

    virtual std::optional<duration> get_time();
    virtual void print(DurationLevel level = DurationLevel::MILLISECONDS);
};


class AccumulatingTimer : public Timer {
private:
    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<std::chrono::high_resolution_clock, duration>;
    
    std::optional<time_point> _start;
    std::optional<time_point> _lastStop;
    std::optional<duration> _currentTime;

public:
    AccumulatingTimer() : Timer("") {}
    AccumulatingTimer(std::string name) : Timer(name) {}

    void reset();
    void start();
    std::optional<duration> stop();

    std::optional<duration> get_time();
};

class MeanTimer : public Timer {
private:
    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<std::chrono::high_resolution_clock, duration>;
    
    std::vector<time_point> _start;
    std::vector<time_point> _stop;

public:
    MeanTimer() : Timer("") {}
    MeanTimer(std::string name) : Timer(name) {}

    void reset();
    void start();
    std::optional<duration> stop();

    std::optional<duration> get_time();
};
};

#endif