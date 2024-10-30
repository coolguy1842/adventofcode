#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <scn/scan.h>
#include <IDay.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

typedef long long DataType;

struct Ingredient {
    std::string name;
    size_t id;

    DataType capacity, durability, flavor, texture, calories;
};

struct CookieRecipe {
    std::vector<size_t> ingredientAmounts = {};
    size_t result = 0;
};

class Day : public AOCUtil::IDay {
private:


public:
    Day() : AOCUtil::IDay(INPUT_PATH) {}

    void partA() {
        std::vector<Ingredient> ingredients;
        for(std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<std::string, DataType, DataType, DataType, DataType, DataType>(line, "{:[^:]}: capacity {}, durability {}, flavor {}, texture {}, calories {}");
            auto [ name, capacity, durability, flavor, texture, calories ] = result->values();

            spdlog::info("{}: {}, {}, {}, {}, {}", name, capacity, durability, flavor, texture, calories);
        }

        CookieRecipe bestRecipe;
        for(size_t i = 0; i < 100; i++) {
            CookieRecipe recipe;

            for(Ingredient& ingredient : ingredients) {
                
            }
        }
    }

    void partB() { }
    

    void printResults(bool partA, bool partB) {

    }
};

#endif