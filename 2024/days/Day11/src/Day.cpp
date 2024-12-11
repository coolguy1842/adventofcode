#include "utils/MathUtils.hpp"
#include <DayInput.hpp>
#include <Day.hpp>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

std::unordered_map<uint64_t, uint64_t> getStones(const std::string& input) {
    std::unordered_map<uint64_t, uint64_t> stones;

    const char* str = input.c_str();

    size_t num;
    char c;
    int read = 0;

    while(sscanf(str += read, "%lu%c%n", &num, &c, &read) == 2) {
        stones[num] += 1;
    }

    stones[num] += 1;

    return stones;
}

void blink(std::unordered_map<uint64_t, uint64_t>& stones) {
    static std::unordered_map<uint64_t, std::vector<uint64_t>> results;
    
    std::unordered_map<uint64_t, uint64_t> nextStones;
    for(auto& pair : stones) {
        const uint64_t& stone = pair.first;
        if(stone == 0) {
            nextStones[1] += pair.second;
            continue;
        }

        top:
        auto res = results[stone];
        if(res.size() > 0) {
            for(const uint64_t& val : res) {
                nextStones[val] += pair.second;
            }

            continue;
        }

        uint64_t numLen = log10(stone) + 1;
        if(numLen % 2 == 0 && numLen > 1) {
            uint64_t pow10 = quick_pow<10>(numLen / 2);
            
            uint64_t lHS = stone / pow10, rHS = stone % pow10;
            results[stone] = { lHS, rHS };
            
            goto top;
        }
        else {
            uint64_t val = pair.first * 2024;

            results[stone] = { val };
            goto top;
        }
    }

    stones = nextStones;
}

uint64_t partFunc(const std::string& input, uint64_t steps) {
    std::unordered_map<uint64_t, uint64_t> stones = getStones(input);

    for(uint64_t i = 0; i < steps; i++) {
        blink(stones);
    }

    size_t out = 0;
    for(const auto& pair : stones) {
        out += pair.second;
    }

    return out;
}

uint64_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text, 25); }
void Day::partB() { bSolution = partFunc(input.text, 75); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}