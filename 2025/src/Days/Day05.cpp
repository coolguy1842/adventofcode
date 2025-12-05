#include <Days/Day05.hpp>
#include <Input/Day05.hpp>
#include <Util/StringUtil.hpp>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <vector>

struct Range {
    uint64_t min;
    uint64_t max;

    bool operator<(const Range& b) const {
        return min < b.min;
    }
};

void Day5::partA() {
    std::list<Range> ranges;
    bool readingRanges = true;

    StringUtil::split(
        input,
        '\n',
        [&](const std::string& str) {
            if(str.empty()) {
                readingRanges = false;
                return;
            }

            if(readingRanges) {
                uint64_t min, max;
                sscanf(str.c_str(), "%lu-%lu", &min, &max);

                ranges.push_back({ min, max });
                return;
            }

            uint64_t id = strtol(str.c_str(), nullptr, 10);
            for(const Range& range : ranges) {
                if(id >= range.min && id <= range.max) {
                    aSolution++;
                    return;
                }
            }
        },
        true
    );
}

void Day5::partB() {
    std::vector<Range> ranges;

    for(const std::string& str : StringUtil::split(input, '\n', true)) {
        if(str.empty()) {
            break;
        }

        uint64_t min, max;
        sscanf(str.c_str(), "%lu-%lu", &min, &max);

        ranges.push_back({ min, max });
    }

    std::sort(ranges.begin(), ranges.end());
    for(auto it = ranges.begin(); it != ranges.end();) {
        Range& a = *it;
        for(auto it2 = it + 1; it2 != ranges.end();) {
            Range& b = *it2;

            if(a.min >= b.min && a.max <= b.max) {
                it = ranges.erase(it);
                goto skip;
            }

            if(a.min <= b.min && a.max >= b.min) {
                if(a.max >= b.max) {
                    it2 = ranges.erase(it2);

                    continue;
                }

                b.min = a.min;

                it = ranges.erase(it);
                goto skip;
            }
            it2++;
        }

        bSolution += (a.max - a.min) + 1;
        it++;
    skip:
    }
}

void Day5::printSolutions(std::bitset<sizeof(IDay::SolutionFlags)> parts) {
    if(parts.test(A)) {
        printf("Part A: %lu\n", aSolution);
    }

    if(parts.test(B)) {
        printf("Part B: %lu\n", bSolution);
    }
}