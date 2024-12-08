#include <DayInput.hpp>
#include <Day.hpp>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <endian.h>
#include <spdlog/spdlog.h>
#include <string>

#include <utils/MathUtils.hpp>

Day::Day() : AOCUtil::IDay(dayInput) {}

bool equalResult(const size_t& result, const size_t* numbers, const size_t& numbersSize, const size_t& _currentVal, const bool& partB) {
    return numbersSize == 0 ? result == _currentVal :
        equalResult(result, numbers + 1, numbersSize - 1, _currentVal + numbers[0], partB) ||
        equalResult(result, numbers + 1, numbersSize - 1, _currentVal * numbers[0], partB) ||
        (
            partB &&
            equalResult(result, numbers + 1, numbersSize - 1, (_currentVal * quick_pow<10>(quick_log10(numbers[0]))) + numbers[0], partB)
        );
}


size_t partFunc(const std::string& input, const bool& partB = false) {
    size_t out = 0;

    // max amount of numbers
    size_t numbers[20];
    const char* str = input.c_str();

    while(*str) {
        size_t result, num;
        int read;
        char c;

        sscanf(str, "%zu: %n", &result, &read);

        size_t numbersSize = 0;
        while(sscanf(str += read, "%zu%c%n", &num, &c, &read) == 2 && c != '\n') {
            numbers[numbersSize++] = num;
        }

        str += read;
        numbers[numbersSize] = num;
 
        if(equalResult(result, numbers + 1, numbersSize, numbers[0], partB)) {
            out += result;
        }
    }

    return out;
}

size_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text); }
void Day::partB() { bSolution = partFunc(input.text, true); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}