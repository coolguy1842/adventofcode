#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <utils/StringUtils.hpp>
#include <IDay.hpp>
#include <algorithm>
#include <cstddef>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    size_t aCombinations, bCombinations;

    void backtrack(const size_t& target, const std::vector<size_t>& containers, std::vector<size_t>& path, std::vector<std::vector<size_t>>& paths, const size_t& start) {
        if(target == 0) {
            paths.push_back(path);
            return;
        }

        for(size_t i = start; i < containers.size(); i++) {
            const size_t& box = containers[i];
            if(box > target) {
                continue;
            }

            path.push_back(box);

            backtrack(target - box, containers, path, paths, i + 1);
            path.pop_back();
        }
    }

    size_t getCombinations(const std::vector<size_t>& containers, const bool& partB = false, const size_t& target = 150) {
        std::vector<std::vector<size_t>> paths;
        std::vector<size_t> path;
        backtrack(target, containers, path, paths, 0);
        
        if(partB) {
            size_t minCount = paths[0].size();
            std::vector<std::vector<size_t>> minResults;
            
            for(const std::vector<size_t>& path : paths) {
                if(path.size() < minCount) {
                    minCount = path.size();
                    minResults = { path };   
                }
                else if(path.size() == minCount) {
                    minResults.push_back(path);
                }
            }

            return minResults.size();
        }
    
        return paths.size();
    }


    std::vector<size_t> initContainers() {
        std::vector<size_t> containers;
        for(std::string& str : input.getSplitText("\n")) {
            containers.push_back(AOCUtil::strtonumeric<size_t>(str.c_str()));
        }

        std::sort(containers.rbegin(), containers.rend());
        return containers;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aCombinations(0), bCombinations(0) {}

    void partA() { aCombinations = getCombinations(initContainers()); }
    void partB() { bCombinations = getCombinations(initContainers(), true ); }

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aCombinations);
        if(partB) spdlog::info("Part B: {}", bCombinations);
    }
};

#endif