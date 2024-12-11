#include <DayInput.hpp>
#include <Day.hpp>
#include <asm-generic/errno.h>
#include <cstdio>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

inline std::vector<std::vector<int64_t>> parseNumbers(const std::string& line) {
    std::vector<std::vector<int64_t>> numbers;

    const char* str = line.c_str();

    int64_t number;
    int read = 0;
    
    std::vector<int64_t> tempNumbers;
    while(sscanf(str, "%ld%n", &number, &read) == 1) {
        tempNumbers.push_back(number);

        str += read;
        if(str[0] == '\n') {
            numbers.push_back(tempNumbers);
            tempNumbers.clear();
        }
    }

    return numbers;
}

enum ELevelDirection {
    INCREASING,
    DECREASING
};

inline bool isSafe(const std::vector<int64_t>& numbers) {
    ELevelDirection direction = numbers[0] > numbers[1] ? DECREASING : INCREASING;
    for(size_t i = 0; i < numbers.size() - 1; i++) {
        const int64_t &left = numbers[i], &right = numbers[i + 1];
        
        if(
            (left == right) ||
            (direction == INCREASING ? left > right : left < right) |
            (std::abs(left - right) > 3)
        ) {
            return false;
        }
    }

    return true;
}


int64_t aSafeReports = 0, bSafeReports = 0;
void Day::partA() {
    for(const std::vector<int64_t>& numbers : parseNumbers(input.text)) {
        if(isSafe(numbers)) {
            aSafeReports++;
        }
    }
}

void Day::partB() {
    for(const std::vector<int64_t>& numbers : parseNumbers(input.text)) {
        for(size_t i = 0; i < numbers.size(); i++) {
            std::vector<int64_t> tempNumbers = numbers;
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