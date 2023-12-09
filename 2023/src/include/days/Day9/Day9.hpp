#ifndef __DAY9_HPP__
#define __DAY9_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>

struct History {
    std::vector<long> values;
    std::vector<long> differences;

    void setValues(std::vector<long> values) {
        this->values = values;
        this->updateDifferences();
    }

    void updateDifferences() {
        differences.clear();

        if(values.size() <= 1) return;
        long prevValue = values[0];

        for(size_t i = 1; i < values.size(); i++) {
            differences.push_back(values[i] - prevValue);
            prevValue = values[i];
        }
    }

    bool isZero() { return std::accumulate(values.begin(), values.end(), 0) == 0; }
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
            while(sscanf(current, "%ld %n", &number, &charsRead) != -1) {
                history.values.push_back(number);
                current += charsRead;
            }

            history.updateDifferences();
            historyList.push_back(history);
        }
    }

    void partA() {
        if(historyList.size() <= 0) loadHistory();
        partASolution = 0;

        for(const History& history : historyList) {
            std::vector<History> subHistoryList;

            History current = history;
            while(!current.isZero()) {
                History newHistory;
                newHistory.setValues(current.differences);
                subHistoryList.push_back(current);

                current = newHistory;
            }

            subHistoryList.push_back(current);
            (subHistoryList.end() - 1).base()->values.push_back(0);

            for(long long i = (long long)subHistoryList.size() - 2; i >= 0; i--) {
                History& sH = subHistoryList[i];
                sH.values.push_back(*(sH.values.end() - 1) + *(subHistoryList[i + 1].values.end() - 1));
            }

            partASolution += *(subHistoryList.begin().base()->values.end() - 1);
        }
    }

    void partB() {
        if(historyList.size() <= 0) loadHistory();
        partBSolution = 0;

        for(const History& history : historyList) {
            std::vector<History> subHistoryList;

            History current = history;
            while(!current.isZero()) {
                History newHistory;
                newHistory.setValues(current.differences);
                subHistoryList.push_back(current);

                current = newHistory;
            }

            subHistoryList.push_back(current);
            (subHistoryList.end() - 1).base()->values.push_back(0);

            for(long long i = (long long)subHistoryList.size() - 2; i >= 0; i--) {
                History& sH = subHistoryList[i];

                sH.values.insert(sH.values.begin(), *(sH.values.begin()) - *(subHistoryList[i + 1].values.begin()));
            }

            partBSolution += *subHistoryList.begin().base()->values.begin();
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day9() : Day("input/day9.txt") {}
};

#endif