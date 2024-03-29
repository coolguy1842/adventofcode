#ifndef __DAY5_HPP__
#define __DAY5_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>
#include <algorithm>
#include <thread>
#include <execution>
#include <mutex>

struct PropertyRange {
    size_t sourceStart;
    size_t sourceEnd;

    size_t destStart;

public:
    bool inRange(size_t value) const { return value >= sourceStart && value < sourceEnd; }
    size_t getDest(size_t value) const { 
        return destStart + (value - sourceStart); 
    } 
};

class Day5 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    std::vector<size_t> seeds;
    std::vector<std::pair<size_t, size_t>> seedRanges;

    std::vector<PropertyRange> seedToSoil;
    std::vector<PropertyRange> soilToFertilizer;
    std::vector<PropertyRange> fertilizerToWater;
    std::vector<PropertyRange> waterToLight;
    std::vector<PropertyRange> lightToTemperature;
    std::vector<PropertyRange> temperatureToHumidity;
    std::vector<PropertyRange> humidityToLocation;

    enum CurrentData {
        NUMBER = 0,
        SOIL,
        FERTILIZER,
        WATER,
        LIGHT,
        TEMPERATURE,
        HUMIDITY,
        LOCATION
    };

public:
    bool inConverter(PropertyRange* foundRange, size_t value, int convertTo) {
        std::vector<PropertyRange>* foundConverter;

        switch (convertTo) {
        case SOIL: foundConverter = &seedToSoil; break;
        case FERTILIZER: foundConverter = &soilToFertilizer; break;
        case WATER: foundConverter = &fertilizerToWater; break;
        case LIGHT: foundConverter = &waterToLight; break;
        case TEMPERATURE: foundConverter = &lightToTemperature; break;
        case HUMIDITY: foundConverter = &temperatureToHumidity; break;
        case LOCATION: foundConverter = &humidityToLocation; break;
        default: break;
        }

        for(const PropertyRange& range : *foundConverter) {
            if(range.inRange(value)) {
                *foundRange = range;
                return true;
            }
        }

        return false;
    }

    void loadSeeds() {
        const char* seedIDPos = this->input[0].c_str() + strlen("seeds: ");
        int nextOffset;

        size_t curSeed;
        while(sscanf(seedIDPos, "%zu %n", &curSeed, &nextOffset) != -1) {
            seeds.push_back(curSeed);
            seedIDPos += nextOffset;
        }
        
        size_t seedStart, seedEnd;
        seedIDPos = this->input[0].c_str() + strlen("seeds: ");
        while(sscanf(seedIDPos, "%zu %zu %n", &seedStart, &seedEnd, &nextOffset) != -1) {
            seedRanges.push_back({seedStart, seedEnd});
            seedIDPos += nextOffset;
        }

        int curData = CurrentData::SOIL;

        size_t curIndex = 3;
        std::string curLine = input[curIndex];

        while(curIndex < input.size()) {
            curLine = input[curIndex];
            while(curIndex < input.size() && input[curIndex].size() > 0) {
                curLine = input[curIndex];
                size_t destinationStart, sourceStart, range;
                sscanf(curLine.c_str(), "%zu %zu %zu", &destinationStart, &sourceStart, &range);

                PropertyRange pRange = {};
                pRange.sourceStart = sourceStart;
                pRange.sourceEnd = sourceStart + range;

                pRange.destStart = destinationStart;

                switch (curData) {
                case CurrentData::SOIL:        seedToSoil.push_back(pRange);            break;
                case CurrentData::FERTILIZER:  soilToFertilizer.push_back(pRange);      break;
                case CurrentData::WATER:       fertilizerToWater.push_back(pRange);     break;
                case CurrentData::LIGHT:       waterToLight.push_back(pRange);          break;
                case CurrentData::TEMPERATURE: lightToTemperature.push_back(pRange);    break;
                case CurrentData::HUMIDITY:    temperatureToHumidity.push_back(pRange); break;
                case CurrentData::LOCATION:    humidityToLocation.push_back(pRange);    break;
                default: break;
                }

                curIndex++;
            }

            curData = (curData + 1);
            curIndex += 2;
        }
    }

    void partA() {
        if(seeds.size() <= 0) loadSeeds();
        partASolution = __LONG_MAX__;

        for(const size_t& seed : seeds) {
            size_t value = seed;
        
            for(int curData = CurrentData::SOIL; curData <= CurrentData::LOCATION; curData++) {
                PropertyRange range;
                if(inConverter(&range, value, curData)) {
                    value = range.getDest(value);
                }
            }

            partASolution = std::min(partASolution, value);
        }
    }


    void partB() {
        if(seeds.size() <= 0) loadSeeds();
        partBSolution = 0;

        std::mutex threadMutex;

        size_t threadMinValue = __LONG_MAX__;
        std::for_each(
            std::execution::par,
            seedRanges.begin(),
            seedRanges.end(),
            [&](auto&& pair) {
                for(size_t seed = pair.first; seed < pair.first + pair.second; seed++) {
                    size_t value = seed;
                
                    for(int curData = CurrentData::SOIL; curData <= CurrentData::LOCATION; curData++) {
                        PropertyRange range;
                        if(inConverter(&range, value, curData)) {
                            value = range.getDest(value);
                        }
                    }

                    threadMutex.lock();
                    threadMinValue = std::min(threadMinValue, value);
                    threadMutex.unlock();
                }
            }
        );

        partBSolution = threadMinValue;
    }
    
    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day5() : Day("input/day5.txt") {}
    ~Day5() {}
};

#endif