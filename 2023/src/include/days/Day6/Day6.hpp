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
    Race partBRace;

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
        

        std::string time = replace(this->input[0], " ", "");
        std::string distance = replace(this->input[1], " ", "");
        sscanf(time.c_str(), "Time:%llu", &partBRace.time);
        sscanf(distance.c_str(), "Distance:%llu", &partBRace.distance);
    }

    bool tryTime(size_t time, size_t limit, size_t best) {
        return time * (limit - time) > best;
    }

    size_t waysToWin(const Race& race) {
        size_t out = 0;
        for(size_t i = 1; i <= race.time; i++) {
            out += i * (race.time - i) > race.distance;
        }

        return out;
    }


    void partA() {
        if(races.size() <= 0) loadTimes();
        partASolution = 1;

        for(const Race& race : races) {
            partASolution *= waysToWin(race);
        }
    }
    
    void partB() {
        if(races.size() <= 0) loadTimes();
        partBSolution = waysToWin(partBRace);
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day6() : Day("input/day6.txt") {}
};

#endif