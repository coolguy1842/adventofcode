#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

enum ItemType {
    WEAPON,
    ARMOR,
    RING
};

struct Item {
    ItemType type;
    std::string name;

    size_t cost;

    struct {
        size_t damage;
        size_t defense;
    } buffs;
};

typedef std::unordered_map<ItemType, std::vector<Item>> TStore;

// very modified dijkstra
namespace RPGstra {

struct PathNode {
    std::unordered_set<Item*> items;
    size_t cost;

    bool hasWeapon = false;
    bool hasArmor = false;
    size_t rings = 0;
};

size_t runA(const TStore& store);

};

class Day : public AOCUtil::IDay {
private:
    TStore initStore() {
        TStore store = {
            {
                WEAPON,
                {
                    { WEAPON, "Dagger",     8,  { 4, 0 } },
                    { WEAPON, "Shortsword", 10, { 5, 0 } },
                    { WEAPON, "Warhammer",  25, { 6, 0 } },
                    { WEAPON, "Longsword",  40, { 7, 0 } },
                    { WEAPON, "Greataxe",   74, { 8, 0 } }
                }
            },
            {
                ARMOR,
                {
                    { ARMOR, "Leather",    13,  { 0, 1 } },
                    { ARMOR, "Chainmail",  31,  { 0, 2 } },
                    { ARMOR, "Splintmail", 53,  { 0, 3 } },
                    { ARMOR, "Bandedmail", 75,  { 0, 4 } },
                    { ARMOR, "Platemail",  102, { 0, 5 } }
                }
            },
            {
                RING,
                {
                    { RING, "Damage +1", 25,  { 1, 0 } },
                    { RING, "Damage +2", 50,  { 1, 0 } },
                    { RING, "Damage +3", 100, { 3, 0 } },

                    { RING, "Defense +1", 20, { 0, 1 } },
                    { RING, "Defense +2", 40, { 0, 1 } },
                    { RING, "Defense +3", 80, { 0, 3 } },
                }
            }
        };

        return store;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH) {}

    void partA();
    void partB();

    void printResults(bool partA, bool partB);
};

#endif