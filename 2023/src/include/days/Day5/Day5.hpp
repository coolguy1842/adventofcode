#ifndef __DAY5_HPP__
#define __DAY5_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>

struct PropertyRange {
    size_t sourceStart;
    size_t sourceEnd;

    size_t destStart;

public:
    bool inRange(size_t value) { return value >= sourceStart && value <= sourceEnd; }
    size_t getDest(size_t value) { return destStart + (sourceStart - value); } 
};

bool operator==(const PropertyRange& a, const PropertyRange& b) {
    return a.start == b.start && a.end == b.end; 
}

struct range_hash {
    inline std::size_t operator()(const PropertyRange& p) const {
        return p.sourceStart * 32 + p.sourceEnd * 16 + p.destStart;
    }
};


class Day5 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    robin_hood::unordered_flat_set<size_t> seeds;

    robin_hood::unordered_flat_set<PropertyRange, range_hash> seedToSoilRanges;
    robin_hood::unordered_flat_set<PropertyRange, range_hash> soilToFertilizer;
    robin_hood::unordered_flat_set<PropertyRange, range_hash> fertilizerToWater;
    robin_hood::unordered_flat_set<PropertyRange, range_hash> waterToLight;
    robin_hood::unordered_flat_set<PropertyRange, range_hash> lightToTemperature;
    robin_hood::unordered_flat_set<PropertyRange, range_hash> temperatureToHumidity;
    robin_hood::unordered_flat_set<PropertyRange, range_hash> humidityToLocation;

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
    bool inConverter(PropertyRange* foundRange, int value, CurrentData convertTo) {
        robin_hood::unordered_flat_set<PropertyRange, range_hash>* foundConverter;

        switch (convertto) {
        case SOIL: foundConverter = &seedToSoilRanges; break;
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
        while(sscanf(seedIDPos, "%lu %n", &curSeed, &nextOffset) != -1) {
            seeds.emplace(curSeed);

            curSeed = {};
            seedIDPos += nextOffset;
        }

        int curData = CurrentData::SOIL;

        size_t curIndex = 3;
        std::string curLine = input[curIndex];
        

        while(curIndex < input.size()) {
            curLine = input[curIndex];
            printf("%s\n", curLine.c_str());

            while(curLine.size()) {
                size_t destinationStart, sourceStart, range;
                sscanf(curLine.c_str(), "%lu %lu %lu", &destinationStart, &sourceStart, &range);

                PropertyRange range = {};
                range.sourceStart = sourceStart;
                range.sourceEnd = sourceStart + range;

                range.destStart = destinationStart;

                switch (curData) {
                case CurrentData::SOIL:        seedToSoil.emplace(destinationRange); break;
                case CurrentData::FERTILIZER:  soilToFertilizer.emplace(destinationRange); break;
                case CurrentData::WATER:       fertilizerToWater.emplace(destinationRange); break;
                case CurrentData::LIGHT:       waterToLight.emplace(destinationRange); break;
                case CurrentData::TEMPERATURE: lightToTemperature.emplace(destinationRange); break;
                case CurrentData::HUMIDITY:    temperatureToHumidity.emplace(destinationRange); break;
                case CurrentData::LOCATION:    humidityToLocation.emplace(destinationRange); break;
                default: break;
                }

                for(size_t i = 0; i < range; i++) {
                    
                }

                curLine = input[++curIndex];
            }
            
            curData = (curData + 1);

            curIndex += 2;
        }

    }

    void partA() {
        if(seeds.size() <= 0) loadSeeds();
        partASolution = 0;

        printf("done loading %lu seeds\n", seeds.size());

        robin_hood::unordered_flat_map<size_t, size_t> seedValues;

        int curData = CurrentData::SOIL;
        while(curData != CurrentData::LOCATION + 1) {
            for(size_t& seed : seeds) {
                size_t value = seedValues[seed];

                switch(curData) {
                case SOIL:
                    if(seedToSoil.contains(seed)) seedValues[seed] = seedToSoil[seed];
                    else seedValues[seed] = seed;
                    break;
                case FERTILIZER: if(soilToFertilizer.contains(value)) seedValues[seed] = soilToFertilizer[value]; break;
                case WATER: if(fertilizerToWater.contains(value)) seedValues[seed] = fertilizerToWater[value]; break;
                case LIGHT: if(waterToLight.contains(value)) seedValues[seed] = waterToLight[value]; break;
                case TEMPERATURE: if(lightToTemperature.contains(value)) seedValues[seed] = lightToTemperature[value]; break;
                case HUMIDITY: if(temperatureToHumidity.contains(value)) seedValues[seed] = temperatureToHumidity[value]; break;
                case LOCATION: if(humidityToLocation.contains(value)) seedValues[seed] = humidityToLocation[value]; break;
                
                default: break;
                }
            } 

            curData++;
        }


        partASolution = -1;
        for(auto& pair : seedValues) {
            partASolution = std::min(partASolution, pair.second);
        }
    }

    void partB() {
        partBSolution = 0;
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %lu\n", partASolution);
        if(partB) printf("partB: %lu\n", partBSolution);
    }

    Day5() : Day("input/day5.txt") {}
};

#endif