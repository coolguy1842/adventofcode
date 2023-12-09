#ifndef __DAY9_HPP__
#define __DAY9_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>

struct History {
    std::vector<std::vector<long>> values;

    void loadSubValues() {
        std::vector<long> valuesList;

        do {
            const std::vector<long>& prevValues = values.back();
            valuesList.clear();

            for(size_t i = 1; i < prevValues.size(); i++) {
                valuesList.push_back(prevValues[i] - prevValues[i - 1]);
            }

            values.push_back(valuesList);
        } while(!isZero(valuesList));
    }

    bool isZero(std::vector<long> values) { return std::accumulate(values.begin(), values.end(), 0) == 0; }
};

class Day9 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    std::vector<History> historyList;

public:
    void loadHistory() {
        for(const std::string& line : input) {
            int charsRead = 0;
            const char* current = line.c_str();

            History history;
            long number;

            history.values.push_back({});
            while(sscanf(current, "%ld %n", &number, &charsRead) != -1) {
                history.values[0].push_back(number);
                current += charsRead;
            }

            history.loadSubValues();
            historyList.push_back(history);
        }
    }

    void partA() {
        if(historyList.size() <= 0) loadHistory();
        partASolution = 0;

        for(History& history : historyList) {
            history.values.back().push_back(0);

            for(long long i = (long long)history.values.size() - 2; i >= 0; i--) {
                std::vector<long>& h = history.values[i];
                h.push_back(h.back() + history.values[i + 1].back());
            }

            partASolution += history.values.front().back();
        }
    }

    void partB() {
        if(historyList.size() <= 0) loadHistory();
        partBSolution = 0;

        for(History& history : historyList) {
            history.values.back().push_back(0);

            for(long long i = (long long)history.values.size() - 2; i >= 0; i--) {
                std::vector<long>& h = history.values[i];
                h.insert(h.begin(), h.front() - history.values[i + 1].front());
            }

            partBSolution += history.values.front().front();
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day9() : Day("input/day9.txt") {}
};

#endif