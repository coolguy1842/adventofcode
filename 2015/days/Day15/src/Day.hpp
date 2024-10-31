#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <cstddef>
#include <cstdlib>
#include <ctime>
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
    std::string name = "";
    DataType capacity = 0, durability = 0, flavor = 0, texture = 0, calories = 0;

    DataType getScore() {
        return capacity * durability * flavor * texture;
    }
};

template<size_t MaxIngredients>
struct CookieRecipe {
private:
    Ingredient emptyIngredient;
    std::optional<DataType> result;

public:
    std::array<const Ingredient*, MaxIngredients> ingredients;
    CookieRecipe() {
        ingredients.fill(&emptyIngredient);
    }

    DataType getResultA() {
        DataType capacity = 0, durability = 0, flavor = 0, texture = 0;
        for(const Ingredient* ingredient : ingredients) {
            capacity += ingredient->capacity;
            durability += ingredient->durability;
            flavor += ingredient->flavor;
            texture += ingredient->texture;
        }

        return std::max(capacity, (DataType)0) * std::max(durability, (DataType)0) * std::max(flavor, (DataType)0) * std::max(texture, (DataType)0);
    }

    DataType getResultB() {
        DataType capacity = 0, durability = 0, flavor = 0, texture = 0, calories = 0;
        for(const Ingredient* ingredient : ingredients) {
            capacity += ingredient->capacity;
            durability += ingredient->durability;
            flavor += ingredient->flavor;
            texture += ingredient->texture;
            calories += ingredient->calories;
        }

        return std::max(capacity, (DataType)0) * std::max(durability, (DataType)0) * std::max(flavor, (DataType)0) * std::max(texture, (DataType)0) * (calories != 500 ? 0 : 1);
    }
};

class Day : public AOCUtil::IDay {
private:
    DataType aSolution;
    DataType bSolution;

    template<size_t Capacity>
    DataType knapSack(const std::vector<Ingredient>& ingredients, const bool& partB = false) {
        DataType prevResult = 0;

        CookieRecipe<Capacity> recipe, prevRecipe;

        srand(time(NULL));

        size_t goes = Capacity;
        if(!partB) {
            goes *= 10;
        }
        else {
            goes *= 1000;
        }

        for(size_t i = 0; i < goes; i++) {
            for(size_t j = 0; j < Capacity; j++) {
                recipe.ingredients[j] = &ingredients[rand() % ingredients.size()];
            }

            DataType res;
            if(!partB) {
                res = recipe.getResultA();
            }
            else {
                res = recipe.getResultB();
            }

            if(res < prevResult) {
                recipe = prevRecipe;
            }
            else {
                prevRecipe = recipe;
                prevResult = res;
            }
        }

        // final adjustments
        for(size_t i = 0; i < ingredients.size(); i++) {
            for(size_t j = 0; j < Capacity; j++) {
                const Ingredient* prev = recipe.ingredients[j];
                recipe.ingredients[j] = &ingredients[i];

                DataType res;
                if(!partB) {
                    res = recipe.getResultA();
                }
                else {
                    res = recipe.getResultB();
                }

                if(prevResult <= res) {
                    prevResult = res;
                }
                else {
                    recipe.ingredients[j] = prev;
                }
            }
        }


        return prevResult;
    }


    std::vector<Ingredient> initIngredients() {
        std::vector<Ingredient> ingredients;
        for(std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<std::string, DataType, DataType, DataType, DataType, DataType>(line, "{:[^:]}: capacity {}, durability {}, flavor {}, texture {}, calories {}");
            auto [ name, capacity, durability, flavor, texture, calories ] = result->values();

            ingredients.push_back({
                name,
                capacity, durability, flavor, texture, calories
            });
        }

        return ingredients;
    }


public:
    Day() : AOCUtil::IDay(INPUT_PATH), aSolution(0), bSolution(0) {}

    void partA() {
        aSolution = knapSack<100>(initIngredients());
    }

    void partB() {
        bSolution = knapSack<100>(initIngredients(), true);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aSolution);
        if(partB) spdlog::info("Part B: {}", bSolution);
    }
};

#endif