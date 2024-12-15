#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>
#include <vector>

#define WIDTH 101
#define HEIGHT 103

#define HALF_WIDTH WIDTH / 2
#define HALF_HEIGHT HEIGHT / 2


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

uint64_t aSolution = 0;
void Day::partA() {
#define SECONDS 100
    const char* str = input.text.c_str();

    uint64_t quadrants[4];
    memset(quadrants, 0, sizeof(quadrants));

    Robot robot;
    int read = 0;
    do {
        sscanf(str, "p=%ld,%ld v=%ld,%ld\n%n", &robot.position.x, &robot.position.y, &robot.velocity.x, &robot.velocity.y, &read);

        // offset by width and height to prevent negative output from modulo: suggestion from u/wurlin_murlin https://www.reddit.com/r/adventofcode/comments/1hdvhvu/comment/m2306c7
        robot.position.x = (robot.position.x + (100 * (robot.velocity.x + WIDTH))) % WIDTH;
        robot.position.y = (robot.position.y + (100 * (robot.velocity.y + HEIGHT))) % HEIGHT;
        if(robot.position.x == HALF_WIDTH || robot.position.y == HALF_HEIGHT) {
            continue;
        }

        // y quadrant shifts over by 1 to put in the 2s place then combine with the x quadrant with or
        quadrants[((robot.position.y > HALF_HEIGHT) << 1) | (robot.position.x > HALF_WIDTH)]++;
    } while(*(str += read));

    aSolution = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
}

uint64_t bSolution = 0;
void Day::partB() {
    const char* str = input.text.c_str();

    // for some reason using the defined WIDTH and HEIGHT makes it run slower so create the variables here
    uint64_t width = 101;
    uint64_t height = 103;

    std::vector<Robot> robots;
    uint32_t distinctRobots[height * width];

    Robot robot;
    int read = 0;
    do {
        sscanf(str, "p=%ld,%ld v=%ld,%ld\n%n", &robot.position.x, &robot.position.y, &robot.velocity.x, &robot.velocity.y, &read);
        robot.velocity.x += width;
        robot.velocity.y += height;

        robots.push_back(robot);
    } while(*(str += read));

    uint32_t i = -1;
    bool isDistributed = false;
    while(!isDistributed) {
        isDistributed = true;
        for(Robot& robot : robots) {
            if(isDistributed) {
                uint32_t& pos = distinctRobots[(robot.position.y * width) + robot.position.x];
                if(pos == i) {
                    isDistributed = false;
                }
                else {
                    pos = i;
                }
            }

            robot.position.x = (robot.position.x + robot.velocity.x) % width;
            robot.position.y = (robot.position.y + robot.velocity.y) % height;
        }

        i++;
    }

    bSolution = i;
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}