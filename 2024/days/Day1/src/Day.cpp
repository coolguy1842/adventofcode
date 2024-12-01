#include <DayInput.hpp>
#include <Day.hpp>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

size_t aSolution = 0;
void Day::partA() {
    std::vector<size_t> leftList, rightList;

    for(std::string& line : input.getSplitText("\n")) {
        size_t left, right;

        sscanf(line.c_str(), "%zu   %zu", &left, &right);
        leftList.push_back(left);
        rightList.push_back(right);
    }

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    for(size_t i = 0; i < leftList.size(); i++) {
        aSolution += std::abs((long long)leftList[i] - (long long)rightList[i]);
    }
}

size_t bSolution = 0;
void Day::partB() {
    std::vector<size_t> leftList;
    std::unordered_map<size_t, size_t> frequency;

    for(std::string& line : input.getSplitText("\n")) {
        size_t left, right;
        sscanf(line.c_str(), "%zu   %zu", &left, &right);
        
        leftList.push_back(left);
        frequency[right]++;
    }

    for(const size_t& i : leftList) {
        bSolution += i * frequency[i];
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}