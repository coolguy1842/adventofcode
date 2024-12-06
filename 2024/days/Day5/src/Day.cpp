#include <DayInput.hpp>
#include <Day.hpp>
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void initRules(const std::vector<std::string>& input, std::unordered_map<size_t, std::unordered_set<size_t>>& rules, std::vector<std::vector<size_t>>& updates) {
    bool doRules = true;
    for(const std::string& str : input) {
        if(str.size() == 0) {
            doRules = false;
            continue;
        }

        if(doRules) {
            size_t left, right;
            sscanf(str.c_str(), "%zu|%zu", &left, &right);

            rules[left].emplace(right);
        }
        else {
            const char* strPtr = str.c_str();
            char c;

            size_t num;
            int read;
            
            std::vector<size_t> update;
            while(sscanf(strPtr, "%zu%c%n", &num, &c, &read) == 2) {
                update.push_back(num);

                strPtr += read;
            }

            update.push_back(num);
            updates.push_back(update);
        }
    }
}

bool isCorrect(const std::unordered_map<size_t, std::unordered_set<size_t>>& rules, const std::vector<size_t>& update) {
    for(size_t i = 0; i < update.size(); i++) {
        const size_t& before = update[i];

        for(size_t j = i + 1; j < update.size(); j++) {
            const size_t& after = update[j];

            if(rules.contains(after) && rules.at(after).contains(before)) {
                return false;
            }
        }
    }

    return true;
}


Day::Day() : AOCUtil::IDay(dayInput) {}

size_t aSolution = 0;
void Day::partA() {
    std::unordered_map<size_t, std::unordered_set<size_t>> rules;
    std::vector<std::vector<size_t>> updates;

    initRules(input.getSplitText("\n"), rules, updates);

    for(const std::vector<size_t>& update : updates) {
        if(isCorrect(rules, update)) {
            aSolution += update[update.size() / 2];
        }
    }
}

size_t bSolution = 0;
void Day::partB() {
    std::unordered_map<size_t, std::unordered_set<size_t>> rules;
    std::vector<std::vector<size_t>> updates;

    initRules(input.getSplitText("\n"), rules, updates);

    for(std::vector<size_t>& update : updates) {
        if(isCorrect(rules, update)) {
            continue;
        }

        std::sort(update.begin(), update.end(), [&rules](size_t& a, size_t& b) {
            return !rules[b].contains(a);
        });

        bSolution += update[update.size() / 2];
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}