#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>

#include <spdlog/spdlog.h>
#include <scn/scan.h>

#include <string>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    typedef std::unordered_map<std::string, std::unordered_map<std::string, long long>> TPreferences;
    long long aSolution;
    long long bSolution;

    struct PreferencesOut {
        TPreferences preferences;
        std::vector<std::string> names;
    };

    PreferencesOut initPreferences() {
        PreferencesOut out;

        for(std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<std::string, std::string, long long, std::string>(line, "{} would {} {} happiness units by sitting next to {:[^.]}");
            auto [ target, action, units, person ] = result->values();

            switch(action[0]) {
            case 'g': break;
            case 'l': units *= -1; break;
            default: 
                spdlog::warn("Invalid unit action {}, skipping.", action);
                continue;
            }

            if(!out.preferences.contains(target)) {
                out.names.push_back(target);
            }

            out.preferences[target][person] = units;
        }

        return out;
    }

    long long maxPermutation(PreferencesOut& pair) {
        TPreferences& preferences = pair.preferences;
        std::vector<std::string>& names = pair.names;

        long long maxHappiness = 0;
        const size_t& numNames = names.size();

        do {
            long long sumHappiness = 0;
            for(size_t i = 0; i < numNames; i++) {
                size_t left = (numNames + (i - 1)) % numNames;
                size_t right = (i + 1) % numNames;
                
                const std::string& leftP = names[left];
                const std::string& target = names[i];
                const std::string& rightP = names[right];

                auto& targetPreferences = preferences[target];

                sumHappiness += targetPreferences[leftP];
                sumHappiness += targetPreferences[rightP];
            }

            if(sumHappiness > maxHappiness) {
                maxHappiness = sumHappiness;
            }
        } while(std::next_permutation(names.begin(), names.end()));

        return maxHappiness;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aSolution(0) {}

    void partA() {
        PreferencesOut res = initPreferences();
        aSolution = maxPermutation(res);
    }

    void partB() {
        PreferencesOut res = initPreferences();

        const std::string selfName = "me";
        for(std::string& name : res.names) {
            res.preferences[selfName][name] = 0;
            res.preferences[name][selfName] = 0;
        }

        res.names.push_back(selfName);
        bSolution = maxPermutation(res);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aSolution);
        if(partB) spdlog::info("Part B: {}", bSolution);
    }
};

#endif