#include <Timer.hpp>

using duration = std::chrono::nanoseconds;
using time_point = std::chrono::time_point<std::chrono::high_resolution_clock, duration>;

void AOCUtil::Timer::start() {
    this->_start = std::chrono::high_resolution_clock::now();
    this->_stop = std::nullopt;
}

std::optional<duration> AOCUtil::Timer::stop() {
    if(!this->_start.has_value()) {
        return this->get_last();
    }

    this->_stop = std::chrono::high_resolution_clock::now();
    return this->get_last();
}

std::optional<duration> AOCUtil::Timer::get_last() {
    if(!this->_start.has_value() || !this->_stop.has_value()) {
        return std::nullopt;
    }

    return std::chrono::duration_cast<duration>(this->_stop.value() - this->_start.value());
}


void AOCUtil::Timer::print(DurationLevel level) {
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