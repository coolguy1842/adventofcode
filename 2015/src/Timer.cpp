#include <Timer.hpp>
#include <optional>

using duration = std::chrono::nanoseconds;
using time_point = std::chrono::time_point<std::chrono::high_resolution_clock, duration>;

void AOCUtil::Timer::start() {
    _start = std::chrono::high_resolution_clock::now();
    _stop = std::nullopt;
}

std::optional<duration> AOCUtil::Timer::stop() {
    if(!_start.has_value()) {
        return this->get_time();
    }

    _stop = std::chrono::high_resolution_clock::now();
    return this->get_time();
}

std::optional<duration> AOCUtil::Timer::get_time() {
    if(!_start.has_value() || !_stop.has_value()) {
        return std::nullopt;
    }

    return std::chrono::duration_cast<duration>(_stop.value() - _start.value());
}


void AOCUtil::Timer::print(DurationLevel level) {
    std::optional<duration> dur = this->get_time();
    if(_name.empty()) {
        spdlog::info("---- Timer ----");
    }
    else {
        spdlog::info("---- Timer {} ----", _name);
    }

    std::string endLine = "--------------";
    if(!_name.empty()) {
        for(size_t i = 0; i <= _name.size(); i++) {
            endLine += "-";
        }

        // extra space
        endLine += "-";
    }

    if(!dur.has_value()) {
        spdlog::info("No start/stop");
        spdlog::info("{}", endLine);
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
    
    spdlog::info("{}", endLine);
}




void AOCUtil::AccumulatingTimer::start() {
    _start = std::chrono::high_resolution_clock::now();
}

std::optional<duration> AOCUtil::AccumulatingTimer::stop() {
    if(!_start.has_value()) {
        return this->get_time();
    }

    _lastStop = std::chrono::high_resolution_clock::now();

    if(!_currentTime.has_value()) {
        _currentTime = std::chrono::duration_cast<duration>(_lastStop.value() - this->_start.value());
    }
    else {
        _currentTime = std::chrono::duration_cast<duration>(_currentTime.value() + (_lastStop.value() - this->_start.value()));
    }

    return this->get_time();
}

void AOCUtil::AccumulatingTimer::reset() {
    _start = std::nullopt;
    _lastStop = std::nullopt;
    _currentTime = std::nullopt;
}



std::optional<duration> AOCUtil::AccumulatingTimer::get_time() {
    if(!_start.has_value() || !_currentTime.has_value()) {
        return std::nullopt;
    }

    return _currentTime.value();
}