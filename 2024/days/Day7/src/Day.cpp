#include <DayInput.hpp>
#include <Day.hpp>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <deque>
#include <endian.h>
#include <functional>
#include <spdlog/spdlog.h>
#include <string>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct Node {
    size_t val;

    const size_t* next;
    const size_t nextSize;
};

inline size_t quick_pow10(const size_t& n) {
    const static size_t pow10[] = { 1, 10, 100, 1000, 10000,  100000, 1000000, 10000000, 100000000, 1000000000 };
    return pow10[n]; 
}

bool canEqual(const size_t& result, const size_t* numbers, const size_t& numbersSize) {
    std::deque<Node> queue;
    
    queue.push_back({ numbers[0], numbers + 1, numbersSize - 1 });
    while(!queue.empty()) {
        const Node& node = queue.front();
        
        if(node.nextSize <= 0) {
            if(node.val == result) {
                return true;
            }

            queue.pop_front();
            continue;
        }

        queue.push_back({ node.val * node.next[0], node.next + 1, node.nextSize - 1 });
        queue.push_back({ node.val + node.next[0], node.next + 1, node.nextSize - 1 });

        queue.pop_front();
    }

    return false;
}

bool canEqualB(const size_t& result, const size_t* numbers, const size_t& numbersSize) {
    std::deque<Node> queue;
    
    queue.push_back({ numbers[0], numbers + 1, numbersSize - 1 });
    while(!queue.empty()) {
        const Node& node = queue.front();
        
        if(node.nextSize <= 0) {
            if(node.val == result) {
                return true;
            }

            goto next;
        }
        
        queue.push_back({ node.val * node.next[0], node.next + 1, node.nextSize - 1 });
        queue.push_back({ node.val + node.next[0], node.next + 1, node.nextSize - 1 });

        queue.push_back({ (node.val * quick_pow10(std::floor(std::log10(node.next[0]) + 1))) + node.next[0], node.next + 1, node.nextSize - 1 });
        
        next:
        queue.pop_front();
    }

    return false;
}


size_t partFunc(const std::string& input, const bool& partA = true) {
    size_t out = 0;

    // max amount of numbers
    size_t numbers[20];

    const char* str = input.c_str();

    std::function<bool(size_t, size_t*, size_t)> checkerFunc;
    if(partA) {
        checkerFunc = &canEqual;
    }
    else {
        checkerFunc = &canEqualB;
    }

    while(*str) {
        size_t result, num;
        char c;
        int read;

        sscanf(str, "%zu: %n", &result, &read);

        size_t numbersSize = 0;
        while(sscanf(str += read, "%zu%c%n", &num, &c, &read) == 2 && c != '\n') {
            numbers[numbersSize++] = num;
        }

        str += read;
        numbers[numbersSize++] = num;
 
        if(checkerFunc(result, numbers, numbersSize)) {
            out += result;
        }
    }

    return out;
}

size_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text); }
void Day::partB() { bSolution = partFunc(input.text, false); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}