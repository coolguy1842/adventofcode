#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <scn/scan.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

#define RACE_SECONDS 2503

struct Reindeer {
    std::string name;

    size_t speed;
    size_t speedTime;

    size_t restTime;

    size_t currentDistance = 0;
    size_t currentPoints = 0;
};

class Day : public AOCUtil::IDay {
private:
    std::vector<Reindeer> initReindeer() {
        std::vector<Reindeer> out;
        for(const std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<std::string, size_t, size_t, size_t>(line, "{} can fly {} km/s for {} seconds, but then must rest for {} seconds.");
            auto [ name, speed, speedTime, restTime ] = result->values();

            out.push_back({
                name,

                speed,
                speedTime,

                restTime
            });
        }

        return out;
    }


    struct LeaderInfo {
        std::vector<Reindeer*> leaders;
        size_t distance = 0;
    };

    size_t aWinnerDistance;
    size_t bWinnerDistance;

    size_t raceA(std::vector<Reindeer>& reindeer, const size_t& raceTime) {
        size_t winDistance = 0;
        for(Reindeer& deer : reindeer) {
            deer.currentDistance = 0;

            for(size_t i = 0; i < raceTime; i += deer.speedTime + deer.restTime) {
                if(i + deer.speedTime >= raceTime) {
                    deer.currentDistance += deer.speed * (raceTime - i);
                    break;
                }

                deer.currentDistance += deer.speed * deer.speedTime;
            } 

            if(deer.currentDistance > winDistance) {
                winDistance = deer.currentDistance;
            }
        }

        return winDistance;
    }


    void interpolatePosition(LeaderInfo* leaders, Reindeer& deer, const size_t& start, const size_t& end, const size_t& step = 0) {
        for(size_t i = start; i < end; i++) {
            deer.currentDistance += step;

            LeaderInfo& leaderPos = leaders[i];
            if(leaderPos.distance < deer.currentDistance) {
                // refund points
                for(Reindeer*& reindeer : leaderPos.leaders) {
                    reindeer->currentPoints--;
                }

                deer.currentPoints++;
                
                leaderPos.leaders = { &deer };
                leaderPos.distance = deer.currentDistance;
            }
            else if(leaderPos.distance == deer.currentDistance) {
                leaderPos.leaders.push_back(&deer);
                deer.currentPoints++;
            }
        }
    }

    size_t raceB(std::vector<Reindeer>& reindeer, const size_t& raceTime) {
        LeaderInfo leaders[raceTime];

        for(Reindeer& deer : reindeer) {
            deer.currentDistance = 0;
            deer.currentPoints = 0;

            for(size_t i = 0; i < raceTime; i += deer.speedTime + deer.restTime) {
                size_t endSpeedSeconds = std::min(i + deer.speedTime, raceTime);
                interpolatePosition(leaders, deer, i, endSpeedSeconds, deer.speed);
                interpolatePosition(leaders, deer, endSpeedSeconds + 1, std::min(endSpeedSeconds + deer.restTime, raceTime), 0);
            } 
        }

        return std::max_element(
            reindeer.begin(),
            reindeer.end(),
            [](const auto& a, const auto& b) {
                return a.currentPoints < b.currentPoints;
            }
        )->currentPoints;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aWinnerDistance(0) {}

    void partA() {
        std::vector<Reindeer> reindeer = initReindeer();
        aWinnerDistance = raceA(reindeer, RACE_SECONDS);
    }

    void partB() {
        std::vector<Reindeer> reindeer = initReindeer();
        bWinnerDistance = raceB(reindeer, RACE_SECONDS);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aWinnerDistance);
        if(partB) spdlog::info("Part B: {}", bWinnerDistance);
    }
};

#endif