#include <DayInput.hpp>
#include <Day.hpp>
#include <cmath>
#include <cstdio>
#include <endian.h>
#include <functional>
#include <queue>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Node {
    size_t res;
    size_t val;

    std::vector<size_t> next;

    auto operator<=>(const Node& other) const {
        return val <=> other.val;
    }
};

bool canEqual(size_t result, std::vector<size_t> numbers) {
    std::priority_queue<Node, std::vector<Node>, std::less<Node>> queue;
    
    queue.push({ result, numbers[0], std::vector<size_t>(numbers.begin() + 1, numbers.end()) });
    while(!queue.empty()) {
        const Node node = queue.top();
        queue.pop();
        
        if(node.next.size() <= 0) {
            if(node.val == result) {
                return true;
            }

            continue;
        }
        
        std::vector<size_t> next = std::vector<size_t>(node.next.begin() + 1, node.next.end());
        queue.push({ result, node.val * node.next[0], next });
        queue.push({ result, node.val + node.next[0], next });
    }

    return false;
}

bool canEqualB(size_t result, std::vector<size_t> numbers) {
    std::priority_queue<Node, std::vector<Node>, std::less<Node>> queue;
    
    queue.push({ result, numbers[0], std::vector<size_t>(numbers.begin() + 1, numbers.end()) });
    while(!queue.empty()) {
        const Node node = queue.top();
        queue.pop();
        
        if(node.next.size() <= 0) {
            if(node.val == result) {
                return true;
            }

            continue;
        }
        
        std::vector<size_t> next = std::vector<size_t>(node.next.begin() + 1, node.next.end());
        queue.push({ result, node.val * node.next[0], next });
        queue.push({ result, node.val + node.next[0], next });

        size_t len = std::floor(std::log10(node.next[0]) + 1);
        queue.push({ result, (node.val * (size_t)std::pow(10, len)) + node.next[0], next });
    }

    return false;
}

size_t aSolution = 0;
void Day::partA() {
    for(const std::string& line : input.getSplitText("\n")) {
        const char* str = line.c_str();

        size_t result, num;
        char c;
        int read;

        sscanf(str, "%zu: %n", &result, &read);

        std::vector<size_t> numbers;
        while(sscanf(str += read, "%zu%c%n", &num, &c, &read) == 2) {
            numbers.push_back(num);
        }

        numbers.push_back(num);

        if(canEqual(result, numbers)) {
            aSolution += result;
        }
    }
}

size_t bSolution = 0;
void Day::partB() {
    for(const std::string& line : input.getSplitText("\n")) {
        const char* str = line.c_str();

        size_t result, num;
        char c;
        int read;

        sscanf(str, "%zu: %n", &result, &read);

        std::vector<size_t> numbers;
        while(sscanf(str += read, "%zu%c%n", &num, &c, &read) == 2) {
            numbers.push_back(num);
        }

        numbers.push_back(num);

        if(canEqualB(result, numbers)) {
            bSolution += result;
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}