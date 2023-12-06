#ifndef __DAY6_HPP__
#define __DAY6_HPP__

#include <day.hpp>
#include <stdio.h>

struct Race {
    size_t time;
    size_t distance;
};

class Day6 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
public:
    std::vector<Race> races;

    void loadTimes() {
        const char* timePos = this->input[0].c_str() + strlen("Time: ");
        int nextOffset;

        size_t curTime;
        while(sscanf(timePos, "%llu %n", &curTime, &nextOffset) != -1) {
            races.push_back(Race { curTime, 0 });
            timePos += nextOffset;
        }

        const char* distancePos = this->input[1].c_str() + strlen("Distance: ");
        size_t curDistance, i = 0;
        while(sscanf(distancePos, "%llu %n", &curDistance, &nextOffset) != -1) {
            races[i++].distance = curDistance;
            distancePos += nextOffset;
        }
        
    }

    bool tryTime(size_t time, size_t limit, size_t best) {
        size_t travelled = 0;
        for(size_t i = time; i < limit; i++) {
            travelled += time;
        }

        return travelled > best;
    }

    void partA() {
        if(races.size() <= 0) loadTimes();
        partASolution = 1;

        for(Race& race : races) {
            size_t waysToWin = 0;

            for(size_t i = 1; i <= race.time; i++) {
                if(tryTime(i, race.time, race.distance)) {
                    waysToWin++;        
                }
            }

            partASolution *= waysToWin;
        }
    }
    
    void partB() {
        if(races.size() <= 0) loadTimes();
        partBSolution = 0;
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day6() : Day("input/day6.txt") {}
};

#endif