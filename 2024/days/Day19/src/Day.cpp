#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

std::unordered_map<std::string, uint64_t> cachedResults;
uint64_t isValid(const char* str, const std::vector<std::string>& patterns, const bool& getFirst, const bool& useCache) {
    if(useCache) {
        auto it = cachedResults.find(str);
        if(it != cachedResults.end()) {
            return it->second;
        }
    }

    uint64_t out = 0;
    for(const std::string& pattern : patterns) {
        if(strncmp(str, pattern.c_str(), pattern.size()) != 0) {
            continue;
        }

        if(str[pattern.size()] == '\0') {
            out++;
            
            if(getFirst) {
                break;
            }
        }

        out += isValid(str + pattern.size(), patterns, getFirst, useCache);
        if(getFirst && out) {
            break;
        }
    }

    if(useCache) {
        cachedResults[str] = out;
    }

    return out;
}

inline uint64_t partFunc(const char* input, const bool& getFirst, const bool& useCache) {
    uint64_t out = 0;
    
    std::vector<std::string> patterns;
    int read;

    char pattern[256], desiredPattern[256], c;
    while(sscanf(input, "%[^,\n]%c%n", pattern, &c, &read)) {
        patterns.push_back(std::string(input, input + read - 1));
        input += read + 1;

        if(c != ',') break;
    }

    while(sscanf(input, "%s\n%n", desiredPattern, &read) == 1) {
        out += isValid(desiredPattern, patterns, getFirst, useCache);
        input += read;
    }

    return out;
}

uint64_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text.c_str(), true, false); }
void Day::partB() { bSolution = partFunc(input.text.c_str(), false, true); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}