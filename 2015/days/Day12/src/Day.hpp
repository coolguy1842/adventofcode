#ifndef __DAY_HPP__
#define __DAY_HPP__

#include "nlohmann/json_fwd.hpp"
#include <IDay.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    long long aSolution;
    long long bSolution;

    long long traverseJSONValue(const nlohmann::json& value, bool partB = false) {
        if(value.is_array()) {
            long long sum = 0;

            for(const nlohmann::json& subval : value) {
                sum += traverseJSONValue(subval, partB);
            }

            return sum;
        }
        else if(value.is_object()) {
            long long sum = 0;

            for(auto& subval : value.items()) {
                if(partB && subval.value().is_string()) {
                    if(subval.value() == "red") {
                        return 0;
                    }
                }

                sum += traverseJSONValue(subval.value(), partB);
            }

            return sum;
        }
        else if(value.is_number_integer()) {
            return value;
        }
        else {
            return 0;
        }
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aSolution(0), bSolution(0) {}

    void partA() {
        // who needs error checking
        nlohmann::json json = nlohmann::json::parse(input.text, nullptr, false);
        aSolution = traverseJSONValue(json);
    }

    void partB() {
        nlohmann::json json = nlohmann::json::parse(input.text, nullptr, false);
        bSolution = traverseJSONValue(json, true);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aSolution);
        if(partB) spdlog::info("Part B: {}", bSolution);
    }
};

#endif