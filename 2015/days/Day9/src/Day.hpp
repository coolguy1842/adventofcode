#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>
#include <algorithm>
#include <functional>
#include <limits>
#include <optional>
#include <queue>
#include <spdlog/spdlog.h>
#include <scn/scan.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif


typedef std::unordered_map<std::string, std::unordered_map<std::string, std::size_t>> TDistance;
namespace Dijkstra {

std::optional<size_t> getDistance(TDistance& distances, const std::string& from, const std::string& to) {
    auto it = distances.find(from);
    if(it == distances.end()) {
        return std::nullopt;
    }

    return it->second[to];
}

struct cell {
    std::unordered_set<std::string> visited;

    std::string name;
    size_t cost = 0;

    auto operator<=>(const cell& other) const { return cost <=> other.cost; }
};



size_t runA(TDistance& distances, std::unordered_set<std::string>& names, size_t maxScore = std::numeric_limits<size_t>::max()) {
    std::priority_queue<cell, std::vector<cell>, std::greater<cell>> queue;
    queue.push({ {}, "", 0 });

    while(!queue.empty()) {
        cell curCell = queue.top();
        queue.pop();

        if(curCell.visited.contains(curCell.name)) {
            continue;
        }

        if(curCell.visited.size() == names.size()) {
            return curCell.cost;
        }

        curCell.visited.emplace(curCell.name);
        for(std::string name : names) {
            if(curCell.visited.contains(name)) {
                continue;
            }

            std::optional<size_t> cellCost = getDistance(distances, curCell.name, name);
            if(!cellCost.has_value()) {
                continue;
            }

            cell newCell = {
                curCell.visited,
                name,
                cellCost.value() + curCell.cost
            };

            queue.push(newCell);
        }
    }

    return maxScore;
}

size_t runB(TDistance& distances, std::unordered_set<std::string>& names, size_t maxScore = std::numeric_limits<size_t>::max()) {
    std::priority_queue<cell, std::vector<cell>, std::greater<cell>> queue;
    queue.push({ {}, "", 0 });

    size_t maxFound = 0;
    while(!queue.empty()) {
        cell curCell = queue.top();
        queue.pop();

        if(curCell.visited.contains(curCell.name)) {
            continue;
        }

        if(curCell.visited.size() == names.size()) {
            maxFound = std::max(curCell.cost, maxFound);
            continue;
        }

        curCell.visited.emplace(curCell.name);
        for(std::string name : names) {
            if(curCell.visited.contains(name)) {
                continue;
            }

            std::optional<size_t> cellCost = getDistance(distances, curCell.name, name);
            if(!cellCost.has_value()) {
                continue;
            }

            cell newCell = {
                curCell.visited,
                name,
                cellCost.value() + curCell.cost
            };

            queue.push(newCell);
        }
    }

    return maxFound;
}
};



class Day : public AOCUtil::IDay {
private:
    size_t aDistance;
    size_t bDistance;



public:
    Day() : AOCUtil::IDay(INPUT_PATH), aDistance(0) {}

    void partA() {
        // from -> list of to -> distance
        std::unordered_set<std::string> names;
        TDistance distances;
     
        for(std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<std::string, std::string, size_t>(line, "{} to {} = {}");
            auto [ from, to, distance ] = result->values();

            distances[from][to] = distance;
            distances[to][from] = distance;

            names.emplace(from);
            names.emplace(to);
        }

        for(const std::string& name : names) {
            distances[name][""] = 0;
            distances[""][name] = 0;
        }

        aDistance = Dijkstra::runA(distances, names);
    }

    void partB() {
        // from -> list of to -> distance
        std::unordered_set<std::string> names;
        TDistance distances;
     
        for(std::string& line : input.getSplitText("\n")) {
            auto result = scn::scan<std::string, std::string, size_t>(line, "{} to {} = {}");
            auto [ from, to, distance ] = result->values();

            distances[from][to] = distance;
            distances[to][from] = distance;

            names.emplace(from);
            names.emplace(to);
        }

        for(const std::string& name : names) {
            distances[name][""] = 0;
            distances[""][name] = 0;
        }

        bDistance = Dijkstra::runB(distances, names);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aDistance);
        if(partB) spdlog::info("Part B: {}", bDistance);
    }
};

#endif