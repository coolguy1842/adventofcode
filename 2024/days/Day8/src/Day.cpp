#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdio>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Position {
    size_t x, y;

    inline std::size_t operator()(const Position& c) const {
        return (c.x << 32) + c.y;
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

inline void addPosition(std::unordered_set<Position, Position>& antinodes, const size_t& gridWidth, const size_t& gridHeight, const Position& newPos) {
    if(newPos.x >= gridWidth) return;
    else if(newPos.y >= gridHeight) return;

    antinodes.emplace(newPos);
}

size_t aSolution = 0;
void Day::partA() {
    const char* str = input.text.c_str();

    std::unordered_map<char, std::vector<Position>> antenna;
    std::unordered_set<Position, Position> antinodes;

    size_t gridWidth = 0, gridHeight, x = 0, y = 0;
    for(size_t i = 0; i < input.text.size(); i++) {
        switch(str[i]) {
        case '.': x++; break;
        case '\n':
            if(gridWidth == 0) {
                gridWidth = i;
                gridHeight = input.text.size() / gridWidth;
            }

            x = 0;
            y++;
            break;
        default:
            antenna[str[i]].push_back({ x++, y });
        }
    }

    for(const auto& frequency : antenna) {
        for(size_t i = 0; i <= frequency.second.size() / 2; i++) {
            const Position& a = frequency.second[i];
            for(size_t j = 0; j <= frequency.second.size() / 2; j++) {
                const Position& b = frequency.second[frequency.second.size() - (1 + j)];

                size_t xDiff = (long)a.x - (long)b.x, yDiff = (long)a.y - (long)b.y;
                if(xDiff == 0 && yDiff == 0) {
                    continue;
                }

                addPosition(antinodes, gridWidth, gridHeight, Position(a.x + xDiff, a.y + yDiff));
                addPosition(antinodes, gridWidth, gridHeight, Position(b.x - xDiff, b.y - yDiff));
            }
        }
    }

    aSolution = antinodes.size();
}

size_t bSolution = 0;
void Day::partB() {
    const char* str = input.text.c_str();

    std::unordered_map<char, std::vector<Position>> antenna;
    std::unordered_set<Position, Position> antinodes;

    size_t gridWidth = 0, gridHeight, x = 0, y = 0;
    for(size_t i = 0; i < input.text.size(); i++) {
        switch(str[i]) {
        case '.': x++; break;
        case '\n':
            if(gridWidth == 0) {
                gridWidth = i;
                gridHeight = input.text.size() / gridWidth;
            }

            x = 0;
            y++;
            break;
        default:
            antenna[str[i]].push_back({ x++, y });
        }
    }

    for(const auto& frequency : antenna) {
        for(size_t i = 0; i <= frequency.second.size() / 2; i++) {
            const Position& a = frequency.second[i];
            for(size_t j = 0; j <= frequency.second.size() / 2; j++) {
                const Position& b = frequency.second[frequency.second.size() - (1 + j)];

                size_t xDiff = (long)a.x - (long)b.x, yDiff = (long)a.y - (long)b.y;
                if(xDiff == 0 && yDiff == 0) continue;

                Position pos = { a.x, a.y };
                do {
                    addPosition(antinodes, gridWidth, gridHeight, Position(pos.x, pos.y));
                } while((pos.x += xDiff) < gridWidth && (pos.y += yDiff) < gridHeight);

                Position pos2 = { b.x, b.y };
                do {
                    addPosition(antinodes, gridWidth, gridHeight, Position(pos2.x, pos2.y));
                } while((pos2.x -= xDiff) < gridWidth && (pos2.y -= yDiff) < gridHeight);
            }
        }
    }

    bSolution = antinodes.size();
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}