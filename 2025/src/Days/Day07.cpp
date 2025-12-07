#include <Days/Day07.hpp>
#include <Input/Day07.hpp>
#include <Util/StringUtil.hpp>
#include <cstring>
#include <list>

void Day7::partA() {
    const char* str = input.c_str();
    const char* end = str + input.size();

    const size_t width = (strchrnul(str, '\n') - str) + 1;

    std::list<const char*> beams = { strchr(str, 'S') };
    while(!beams.empty()) {
        const char* beam = beams.front();
        beams.pop_front();

        if(beam + width >= end) {
            continue;
        }

        if(beam[width] != '^') {
            beams.push_back(beam + width);
            continue;
        }

        const char* left  = beam + (width - 1);
        const char* right = beam + (width + 1);

        bool didSplit = false;
        if(std::find(beams.begin(), beams.end(), left) == beams.end()) {
            beams.push_back(left);
            didSplit = true;
        }

        if(std::find(beams.begin(), beams.end(), right) == beams.end()) {
            beams.push_back(right);
            didSplit = true;
        }

        if(didSplit) {
            aSolution++;
        }
    }
}

uint64_t numBeams(const char* beam, size_t width, const char* end) {
    static std::unordered_map<const char*, uint64_t> cache;
    if(cache.contains(beam)) {
        return cache[beam];
    }

    uint64_t beams = 0;
    if(beam + width >= end) {
        beams = 1;
        goto done;
    }

    if(beam[width] != '^') {
        beams = numBeams(beam + width, width, end);
        goto done;
    }

    beams = numBeams(beam + width - 1, width, end);
    beams += numBeams(beam + width + 1, width, end);

done:
    cache[beam] = beams;
    return beams;
}

// 682 not right
void Day7::partB() {
    const char* str = input.c_str();
    const char* end = str + input.size();

    const size_t width = (strchrnul(str, '\n') - str) + 1;
    bSolution += numBeams(strchr(str, 'S'), width, end);
}

void Day7::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}