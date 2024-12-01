#include <DayInput.hpp>
#include <Day.hpp>
#include <algorithm>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

size_t aSolution = 0;
void Day::partA() {
    std::vector<size_t> leftList, rightList;
    std::vector<size_t> leftListSorted, rightListSorted;

    for(std::string& line : input.getSplitText("\n")) {
        size_t left, right;

        sscanf(line.c_str(), "%zu   %zu", &left, &right);
        leftList.push_back(left);
        rightList.push_back(right);
    }

    leftListSorted = std::vector<size_t>(leftList.begin(), leftList.end()); std::sort(leftListSorted.begin(), leftListSorted.end());
    rightListSorted = std::vector<size_t>(rightList.begin(), rightList.end()); std::sort(rightListSorted.begin(), rightListSorted.end());

    for(size_t i = 0; i < leftList.size(); i++) {
        auto& left = leftListSorted[i], &right = rightListSorted[i];
        
        aSolution += std::abs((long long)left - (long long)right);
    }
}

size_t bSolution = 0;
void Day::partB() {
    std::vector<size_t> leftList, rightList;
    std::unordered_map<size_t, size_t> frequency;

    for(std::string& line : input.getSplitText("\n")) {
        size_t left, right;

        sscanf(line.c_str(), "%zu   %zu", &left, &right);
        leftList.push_back(left);
        rightList.push_back(right);
    }

    for(size_t i : rightList) {
        if(!frequency.contains(i)) {
            frequency[i] = 1;
            continue;
        }

        frequency[i]++;
    }

    for(size_t i : leftList) {
        bSolution += i * frequency[i];
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}