#include <DayInput.hpp>
#include <Day.hpp>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Position {
    uint64_t x, y;
};

inline uint64_t getPresses(const Position& a, const Position& b, const Position& p, const bool& partA) {
    // (p.y * b.x - p.x * b.y) / (a.y * b.x - a.x * b.y)
    const auto [ aPresses, aIsValid ] = lldiv(p.y * b.x - p.x * b.y, a.y * b.x - a.x * b.y);
    if(aIsValid != 0 || (partA && aPresses > 100)) return 0;

    // (p.x - a * a.x) / b.x
    const auto [ bPresses, bIsValid ] = lldiv(p.x - aPresses * a.x, b.x);
    if(bIsValid != 0 || (partA && bPresses > 100)) return 0;
    
    return (aPresses * 3) + bPresses;
}

uint64_t partFunc(const std::string& input, const bool& partA) {
    const char* str = input.c_str();
    uint64_t out = 0, offset = partA ? 0 : 10000000000000;

    Position a, b, p;
    int read = 0;
    while(*(str += read)) {
        sscanf(str, "Button A: X+%ld, Y+%ld\nButton B: X+%ld, Y+%ld\nPrize: X=%ld, Y=%ld\n%n", &a.x, &a.y, &b.x, &b.y, &p.x, &p.y, &read);

        p.x += offset; p.y += offset;
        out += getPresses(a, b, p, partA);
    }

    return out;
}

size_t aTotalTokens = 0, bTotalTokens = 0;
void Day::partA() { aTotalTokens = partFunc(input.text, true); }
void Day::partB() { bTotalTokens = partFunc(input.text, false); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aTotalTokens);
    if(partB) spdlog::info("Part B: {}", bTotalTokens);
}