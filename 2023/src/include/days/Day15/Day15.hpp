#ifndef __DAY15_HPP__
#define __DAY15_HPP__

#include <day.hpp>
#include <stdio.h>

class Day15 : public AOC::Day {
private:
    size_t partASolution;
    size_t partBSolution;
    
public:
    size_t hash(std::string str) {
        size_t out = 0;
        for(const char& c : str) {
            out += c;
            out *= 17;
            out %= 256;
        }

        return out;
    }

    void partA() {
        partASolution = 0;
        
        for(std::string& step : split(replace(replace(rawInput, "\r", ""), "\n", ""), ",")) {
            partASolution += hash(step);
        }
    }


    void boxRemoveLabel(std::vector<std::string>& box, std::string& label) {
        for(auto it = box.begin(); it != box.end(); it++) {
            if(*it == label) {
                box.erase(it);
                return;
            }
        }
    }

    void partB() {
        std::vector<std::string> boxes[256];
        // value is the box, focal length
        robin_hood::unordered_flat_map<std::string, std::pair<size_t, char>> labels;
        partBSolution = 0;
        
        for(std::string& step : split(replace(replace(rawInput, "\r", ""), "\n", ""), ",")) {
            if(step.back() == '-') {
                std::string key = step.substr(0, step.size() - 1);

                boxRemoveLabel(boxes[labels[key].first], key);
                labels.erase(key);
                
                continue;    
            }
            
            std::string key = step.substr(0, step.size() - 2);
            char power = step.back() - '0';

            if(labels.contains(key)) {
                labels[key].second = power;
                continue;
            }
            
            size_t box = hash(key);
            boxes[box].push_back(key);

            labels[key] = std::make_pair(box, power);
        }

        for(size_t i : range(256)) {
            for(size_t j : range(boxes[i].size())) {
                partBSolution += (i + 1) * (j + 1) * (labels[boxes[i][j]].second);
            }   
        }
    }

    void printSolution(bool partA, bool partB) {
        if(partA) printf("partA: %zu\n", partASolution);
        if(partB) printf("partB: %zu\n", partBSolution);
    }

    Day15() : Day("input/day15.txt") {}
};

#endif