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
    void start() {
        this->_start = std::chrono::high_resolution_clock::now();
        this->_stop = std::nullopt;
    }

    std::optional<duration> stop() {
        if(!this->_start.has_value()) {
            return this->get_last();
        }

        this->_stop = std::chrono::high_resolution_clock::now();
        return this->get_last();
    }


    std::optional<duration> get_last() {
        if(!this->_start.has_value() || !this->_stop.has_value()) {
            return std::nullopt;
        }

        return std::chrono::duration_cast<duration>(this->_stop.value() - this->_start.value());
    }

    void print(DurationLevel level = DurationLevel::MILLISECONDS) {
        std::optional<duration> dur = this->get_last();
        spdlog::info("---- Time ----");

        if(!dur.has_value()) {
            spdlog::info("No start/stop");
            spdlog::info("--------------");
            return;
        }


        switch(level) {
        case DurationLevel::NANOSECONDS:
            spdlog::info("Nanoseconds: {}", std::chrono::duration_cast<std::chrono::nanoseconds>(dur.value()).count());
        case DurationLevel::MICROSECONDS:
            spdlog::info("Microseconds: {}", std::chrono::duration_cast<std::chrono::nanoseconds>(dur.value()).count() / 1000.0f);
        case DurationLevel::MILLISECONDS:
            spdlog::info("Milliseconds: {}", std::chrono::duration_cast<std::chrono::microseconds>(dur.value()).count() / 1000.0f);
        default:
            spdlog::info("Seconds: {}", std::chrono::duration_cast<std::chrono::milliseconds>(dur.value()).count() / 1000.0f);
            break;
        }
        
        spdlog::info("--------------");
    }
};

};

#endif