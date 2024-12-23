#include <Day.hpp>

size_t Day::getHouse(size_t* houses, const size_t& numHouses, const size_t& findAmount, const size_t& elfDeliverCount, const size_t& elfDeliverMultiplier) {
    // elves
    for(size_t i = 1; i <= numHouses; i++) {
        // houses
        for(size_t j = 1; j <= elfDeliverCount; j++) {
            size_t house = (i * j) - 1;
            if(house > numHouses) {
                break;
            }

            houses[house] += i * elfDeliverMultiplier;
            if(houses[house] >= findAmount) {
                return house + 1;
            }
        }
    }

    return 0;
}


void Day::partA() {
    // start it out at a big number to stop a few reallocs and unnecessary calculations
    size_t numHouses = 1000000, findAmount = AOCUtil::strtonumeric<size_t>(input.text.c_str());
    
    size_t* houses = (size_t*)calloc(numHouses, sizeof(size_t));
    memset(houses, 0, numHouses * sizeof(size_t));

    while(true) {
        aHouseNumber = getHouse(houses, numHouses, findAmount, numHouses, 10);
        if(aHouseNumber != 0) {
            break;
        }

        numHouses *= 10;
        free(houses);

        houses = (size_t*)calloc(numHouses, sizeof(size_t));
        memset(houses, 0, numHouses);
    }

    free(houses);
}

void Day::partB() {
    // start it out at a big number to stop a few reallocs and unnecessary calculations
    size_t numHouses = 100000, findAmount = AOCUtil::strtonumeric<size_t>(input.text.c_str());
    
    size_t* houses = (size_t*)calloc(numHouses, sizeof(size_t));
    memset(houses, 0, numHouses * sizeof(size_t));

    while(true) {
        bHouseNumber = getHouse(houses, numHouses, findAmount, 50, 11);
        if(bHouseNumber != 0) {
            break;
        }

        size_t start = numHouses * sizeof(size_t);
        numHouses *= 10;

        free(houses);

        houses = (size_t*)calloc(numHouses, sizeof(size_t));
        memset(houses, 0, numHouses);
    }

    free(houses);
}


void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aHouseNumber);
    if(partB) spdlog::info("Part B: {}", bHouseNumber);
}