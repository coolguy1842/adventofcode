#include <DayInput.hpp>
#include <Day.hpp>
#include <asm-generic/errno.h>
#include <cstdio>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

inline std::vector<long> parseNumbers(const std::string& line) {
    std::vector<long> numbers;

    const char* str = line.c_str();

    long number;
    int read = 0;
    while(sscanf(str += read, "%ld %n", &number, &read) == 1) {
        numbers.push_back(number);
    }

    return numbers;
}

enum ELevelDirection {
    NONE,
    INCREASING,
    DECREASING
};

inline bool isSafe(const std::vector<long>& numbers) {
    ELevelDirection direction = ELevelDirection::NONE;
    for(size_t i = 0; i < numbers.size() - 1; i++) {
        const long& left = numbers[i];
        const long& right = numbers[i + 1];

        long distance = std::abs(left - right);

        if(distance < 1 || distance > 3) {
            return false;  
        }

        switch(direction) {
        case NONE: direction = left > right ? DECREASING : INCREASING; break;
        case INCREASING: if(left > right) return false; break;
        case DECREASING: if(left < right) return false; break;
        default: break;
        }
    }

    return true;
}


size_t aSafeReports = 0, bSafeReports = 0;
void Day::partA() {
    for(const std::string& line : input.getSplitText("\n")) {
        std::vector<long> numbers = parseNumbers(line);

        if(isSafe(numbers)) {
            aSafeReports++;
        }
    }
}

void Day::partB() {
    for(const std::string& line : input.getSplitText("\n")) {
        std::vector<long> numbers = parseNumbers(line);
        
        for(size_t i = 0; i < numbers.size(); i++) {
            std::vector<long> tempNumbers = numbers;
            tempNumbers.erase(tempNumbers.begin() + i);
            
            if(isSafe(tempNumbers)) {
                bSafeReports++;
                break;
            }
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSafeReports);
    if(partB) spdlog::info("Part B: {}", bSafeReports);
}