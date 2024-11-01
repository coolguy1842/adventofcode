#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <algorithm>
#include <array>
#include <cstddef>
#include <IDay.hpp>
#include <cstring>
#include <execution>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

struct Aunt {
    size_t id;

    std::optional<size_t> children, cats, samoyeds, pomeranians, akitas, vizslas, goldfish, trees, cars, perfumes;
    void loadValue(const char* name, const size_t& value) {
        switch (name[0]) {
        case 'c':
            switch(name[2]) {
            case 'i': children = value; return;
            case 't': cats = value; return;
            case 'r': cars = value; return;
            default: return;
            }
        case 's': samoyeds = value; return;
        case 'p':
            switch (name[1]) {
            case 'o': pomeranians = value; return;
            case 'e': perfumes = value; return;
            default: return;
            }
        case 'a': akitas = value; return;
        case 'v': vizslas = value; return;
        case 'g': goldfish = value; return;
        case 't': trees = value; return;
        }
    }
};

enum ValueCondition {
    EQUALS,
    LESS_THAN,
    GREATER_THAN
};

class Day : public AOCUtil::IDay {
private:
    std::optional<size_t> aAunt, bAunt;

    static bool valueEquals(const std::optional<size_t>& val, const size_t& expected) {
        // presume true
        if(!val.has_value()) return true;
        return val.value() == expected;
    }

    static bool valueConditional(const std::optional<size_t>& val, const size_t& expected, ValueCondition condition) {
        // presume true
        if(!val.has_value()) return true;

        switch(condition) {
        case ValueCondition::EQUALS:       return val.value() == expected;
        case ValueCondition::LESS_THAN:    return val.value() <  expected;
        case ValueCondition::GREATER_THAN: return val.value() >  expected;
        default: return true;
        }
    }

    template<size_t AuntsCount>
    std::optional<size_t> findAunt(const std::array<Aunt, AuntsCount>& aunts, const bool& partB = false) {
        const static size_t children = 3, cats = 7, samoyeds = 2, pomeranians = 3, akitas = 0, vizslas = 0, goldfish = 5, trees = 3, cars = 2, perfumes = 1;

        std::optional<size_t> foundAunt = 0;
        std::for_each(
            std::execution::par_unseq,
            aunts.begin(),
            aunts.end(),
            [&foundAunt, &partB](const Aunt& aunt) {
                if(
                    (partB ?
                        valueConditional(aunt.cats, cats, ValueCondition::GREATER_THAN) &&
                        valueConditional(aunt.trees, trees, ValueCondition::GREATER_THAN) &&
                        valueConditional(aunt.pomeranians, pomeranians, ValueCondition::LESS_THAN) &&
                        valueConditional(aunt.goldfish, goldfish, ValueCondition::LESS_THAN)
                        :
                        valueEquals(aunt.cats, cats) &&
                        valueEquals(aunt.trees, trees) &&
                        valueEquals(aunt.pomeranians, pomeranians) &&
                        valueEquals(aunt.goldfish, goldfish)
                    ) &&
                    valueEquals(aunt.children, children) &&
                    valueEquals(aunt.samoyeds, samoyeds) &&
                    valueEquals(aunt.akitas, akitas) &&
                    valueEquals(aunt.vizslas, vizslas) &&
                    valueEquals(aunt.cars, cars) &&
                    valueEquals(aunt.perfumes, perfumes)
                ) {
                    foundAunt = aunt.id;
                }
            }
        );
        
        return foundAunt;
    }


    template<size_t AuntsCount>
    std::array<Aunt, AuntsCount> initAunts() {
        std::vector<std::string>& splitLines = input.getSplitText("\n");

        std::array<Aunt, AuntsCount> aunts;
        std::for_each(
            std::execution::par_unseq,
            splitLines.begin(),
            splitLines.end(),
            [&aunts](const std::string& line) {
                char valueNames[16], *first = valueNames, *second = valueNames + 3, *third = valueNames + 6;
                size_t id, firstVal, secondVal, thirdVal;
                
                sscanf(line.c_str(), "Sue %zu: %s %zu, %s %zu, %s %zu", &id, first, &firstVal, second, &secondVal, third, &thirdVal);

                Aunt& aunt = aunts[id - 1];
                aunt.id = id;
                aunt.loadValue(first, firstVal);
                aunt.loadValue(second, secondVal);
                aunt.loadValue(third, thirdVal);
            }
        );

        return aunts;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH) {}

    void partA() {
        aAunt = findAunt(initAunts<500>());
    }

    void partB() {
        bAunt = findAunt(initAunts<500>(), true);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) {
            if(aAunt.has_value()) {
                spdlog::info("Part A: {}", aAunt.value());
            }
            else {
                spdlog::info("Part A: Invalid Input");
            }
        }

        if(partB) {
            if(bAunt.has_value()) {
                spdlog::info("Part B: {}", bAunt.value());
            }
            else {
                spdlog::info("Part B: Invalid Input");
            }
        }
    }
};

#endif