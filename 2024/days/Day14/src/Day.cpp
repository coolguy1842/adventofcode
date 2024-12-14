#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Robot {
    struct {
        int64_t x;
        int64_t y;
    } position;

    struct {
        int64_t x;
        int64_t y;
    } velocity;
};

int64_t mod(int64_t a, int64_t b) {
    int64_t result = a % b;
    if(result < 0) {
        result += b;
    }

    return result;
}

uint64_t aSolution = 0;
void Day::partA() {
    const char* str = input.text.c_str();

    uint64_t quadrants[4];
    memset(quadrants, 0, sizeof(quadrants));

    uint64_t width = 101, height = 103;
    uint64_t halfWidth = width / 2, halfHeight = height / 2;

    Robot robot;
    int read = 0;
    do {
        sscanf(str, "p=%ld,%ld v=%ld,%ld\n%n", &robot.position.x, &robot.position.y, &robot.velocity.x, &robot.velocity.y, &read);

        robot.position.x = mod(robot.position.x + (robot.velocity.x * 100), width);
        robot.position.y = mod(robot.position.y + (robot.velocity.y * 100), height);
        if(robot.position.x == halfWidth || robot.position.y == halfHeight) {
            continue;
        }

        quadrants[((robot.position.y > halfHeight) * 2) + (robot.position.x > halfWidth)]++;
    } while(*(str += read));

    aSolution = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
}

uint64_t bSolution = 0;
void Day::partB() {
    const char* str = input.text.c_str();

    std::vector<Robot> robots;

    uint64_t width = 101, height = 103;
    uint64_t distinctRobots[height + 1][width + 1];
    for(uint64_t* row : distinctRobots) {
        memset(row, -1, width * sizeof(uint64_t));
    }

    Robot robot;
    int read = 0;
    do {
        sscanf(str, "p=%ld,%ld v=%ld,%ld\n%n", &robot.position.x, &robot.position.y, &robot.velocity.x, &robot.velocity.y, &read);
        robots.push_back(robot);
    } while(*(str += read));

    uint64_t i = -1;
    bool isDistributed = false;
    while(!isDistributed) {
        isDistributed = true;
        for(Robot& robot : robots) {
            if(isDistributed) {
                uint64_t& pos = distinctRobots[robot.position.y][robot.position.x];
                if(pos == i) {
                    isDistributed = false;
                }
                else {
                    pos = i;
                }
            }

            robot.position.x = mod(robot.position.x + robot.velocity.x, width);
            robot.position.y = mod(robot.position.y + robot.velocity.y, height);
        }

        i++;
    }

    bSolution = i;
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}