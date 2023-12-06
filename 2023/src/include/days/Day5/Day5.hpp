#ifndef __DAY5_HPP__
#define __DAY5_HPP__

#include <day.hpp>
#include <stdio.h>

#include <robin_hood.hpp>

class Day5 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
    robin_hood::unordered_flat_set<size_t> seeds;

    struct Range {
        size_t start;
        size_t end;

        bool inRange(size_t value) { return value >= start && value <= end; } 
    };


    robin_hood::unordered_flat_map<Range, Range> seedToSoilRanges;
    robin_hood::unordered_flat_map<Range, Range> soilToFertilizer;
    robin_hood::unordered_flat_map<Range, Range> fertilizerToWater;
    robin_hood::unordered_flat_map<Range, Range> waterToLight;
    robin_hood::unordered_flat_map<Range, Range> lightToTemperature;
    robin_hood::unordered_flat_map<Range, Range> temperatureToHumidity;
    robin_hood::unordered_flat_map<Range, Range> humidityToLocation; 

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
    void loadSeeds() {
        const char* seedIDPos = this->input[0].c_str() + strlen("seeds: ");
        int nextOffset;

        size_t curSeed;
        while(sscanf(seedIDPos, "%llu %n", &curSeed, &nextOffset) != -1) {
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
                sscanf(curLine.c_str(), "%llu %llu %llu", &destinationStart, &sourceStart, &range);

                Range destinationRange = {};
                destinationRange.start = destinationStart;
                destinationRange.end = destinationStart + range;

                Range sourceRange = {};
                sourceRange.start = sourceStart;
                sourceRange.end = sourceStart + range;

                switch (curData) {
                case CurrentData::SOIL:        seedToSoil[sourceRange] =            destinationRange; break;
                case CurrentData::FERTILIZER:  soilToFertilizer[sourceRange] =      destinationRange; break;
                case CurrentData::WATER:       fertilizerToWater[sourceRange] =     destinationRange; break;
                case CurrentData::LIGHT:       waterToLight[sourceRange] =          destinationRange; break;
                case CurrentData::TEMPERATURE: lightToTemperature[sourceRange] =    destinationRange; break;
                case CurrentData::HUMIDITY:    temperatureToHumidity[sourceRange] = destinationRange; break;
                case CurrentData::LOCATION:    humidityToLocation[sourceRange] =    destinationRange; break;
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

        printf("done loading %llu seeds\n", seeds.size());

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
        if(partA) printf("partA: %llu\n", partASolution);
        if(partB) printf("partB: %llu\n", partBSolution);
    }

    Day5() : Day("input/day5.txt") {}
};

#endif