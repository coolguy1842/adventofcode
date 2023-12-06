#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <chrono>
#include <stdio.h>


namespace AOC {

class Timer {
private:
    std::string name;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    bool hasStart;

    std::chrono::time_point<std::chrono::high_resolution_clock> stopTime;
    bool hasStop;

public:
    Timer(std::string name) : name(name) {}

    void start() {
        startTime = std::chrono::high_resolution_clock::now();
        if(startTime > stopTime) {
            hasStop = false;
        }

        hasStart = true;
    }

    void stop() {
        if(!hasStart) return;
        
        stopTime = std::chrono::high_resolution_clock::now();
        hasStop = true;
    }

    void print() {
        if(!hasStart || !hasStop) return;

        std::string dashes = "";
        for(size_t i = 0; i < this->name.size(); i++) { dashes += "-"; }

        long long nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime - startTime).count();

        printf(
"\n---- %s ----\n" \
"seconds: %f\n" \
"milliseconds %f\n" \
"microseconds %f\n" \
"nanoseconds %lld\n" \
"-----%s-----\n",
name.c_str(),
(double)nanoseconds / (double)1e+9,
(double)nanoseconds / (double)1e+6,
(double)nanoseconds / (double)1000,
nanoseconds,
dashes.c_str()
        );
    }
};

}

#endif