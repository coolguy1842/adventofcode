#ifndef __DAY12_HPP__
#define __DAY12_HPP__

#include <day.hpp>
#include <stdio.h>

#include <iostream>
#include <robin_hood.hpp>

#include <util/range.hpp>

enum SpringType {
    OPERATIONAL = '.',
    DAMAGED = '#',
    UNKNOWN = '?'
};

class Row {
public:
    std::vector<SpringType> springs;
    std::vector<size_t> damagedGroups;
    
    std::vector<SpringType> springsB;
    std::vector<size_t> damagedGroupsB;

    robin_hood::unordered_flat_map<std::pair<size_t, size_t>, size_t, pair_hash> cache;
    robin_hood::unordered_flat_map<std::pair<size_t, size_t>, size_t, pair_hash> cacheB;

private:
    void loadSprings(const std::string& row) {
        std::vector<std::string> rowInfo = split(row, " ");

        for(const char& c : rowInfo[0]) {
            springs.push_back((SpringType)c);
        }

        for(const std::string& group : split(rowInfo[1], ",")) {
            damagedGroups.push_back(strtoull(group.c_str()));
        }


        springsB.reserve(springs.size() * 5);
        damagedGroupsB.reserve(damagedGroups.size() * 5);

        for(size_t i : range(5)) {
            for(size_t j : range(springs.size())) {
                springsB.push_back(springs[j]);
            }

            for(size_t j : range(damagedGroups.size())) {
                damagedGroupsB.push_back(damagedGroups[j]);
            }

            if(i < 4) springsB.push_back(SpringType::UNKNOWN);
        }

        springs.push_back(SpringType::OPERATIONAL);
        springsB.push_back(SpringType::OPERATIONAL);
    }


    bool matches2(size_t pos, size_t len, std::vector<SpringType>& springs) {
        if(pos > 0 && (springs[pos - 1] == SpringType::DAMAGED)) {
            return false;
        }

        if(pos + len > springs.size()) {
            return false;
        }
    
        for(size_t i : range(len)) {
            if(springs[pos + i] == SpringType::OPERATIONAL) {
                return false;
            }
        }

        if(pos + len == springs.size()) {
            return true;
        }

        return springs[pos + len] != SpringType::DAMAGED;
    }

    size_t calculate(size_t pos, size_t group, std::vector<SpringType>& springs, std::vector<size_t>& damagedGroups, robin_hood::unordered_flat_map<std::pair<size_t, size_t>, size_t, pair_hash>& cache) {
        std::pair mapKey = std::make_pair(pos, group);
        if(cache.contains(mapKey)) return cache[mapKey];

        if(group >= damagedGroups.size()) {
            for (auto p : range(pos, springs.size())) 
                if(springs[p] == SpringType::DAMAGED) return 0;

            return 1;
        }

        size_t result = 0;
        while(pos < springs.size()) {
            if(matches2(pos, damagedGroups[group], springs)) {
                result += calculate(pos + damagedGroups[group] + 1, group + 1, springs, damagedGroups, cache);
            }

            if(springs[pos] == SpringType::DAMAGED) break;
            ++pos;
        }

        cache[mapKey] = result;
        return result;
    }

public:
    Row(const std::string& row) {
        loadSprings(row);
    }
    
    size_t arrangements(bool partA) {
        if(partA) return calculate(0, 0, springs, damagedGroups, cache);
        return calculate(0, 0, springsB, damagedGroupsB, cacheB);
    }
};

class Day12 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    std::vector<Row> rows;

public:
    void loadRows() {
        for(const std::string& line : input) {
            rows.push_back(Row(line));
        }
    }

    void partA() {
        if(rows.size() <= 0) loadRows();
        partASolution = 0;

        for(Row& row : rows) {
            partASolution += row.arrangements(true);
        }
    }

    void partB() {
        if(rows.size() <= 0) loadRows();
        partBSolution = 0;

        for(Row& row : rows) {
            partBSolution += row.arrangements(false);
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day12() : Day("input/day12.txt") {}
};

#endif