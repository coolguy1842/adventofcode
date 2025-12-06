#include <Days/Day05.hpp>
#include <Input/Day05.hpp>
#include <Util/StringUtil.hpp>
#include <algorithm>
#include <cstdint>
#include <vector>

struct Range {
    uint64_t min;
    uint64_t max;

    bool operator<(const Range& other) const {
        return min < other.min;
    }
};

// returns number of unique ids
inline void mergeRanges(std::vector<Range>& ranges) {
    std::sort(ranges.begin(), ranges.end());
    for(auto it = ranges.begin(); it != ranges.end(); it++) {
        Range& a = *it;

        for(auto it2 = it + 1; it2 != ranges.end();) {
            const Range& b = *it2;

            // if a is inside b, remove b and merge min/maxes
            if(a.min <= b.min && a.max >= b.min) {
                a.min = std::min(a.min, b.min);
                a.max = std::max(a.max, b.max);

                it2 = ranges.erase(it2);
                continue;
            }

            it2++;
        }
    }
}

void Day5::partA() {
    std::vector<Range> ranges;
    for(char* str = const_cast<char*>(input.c_str()); *str != '\0';) {
        const uint64_t val = strtoul(str, &str, 10);
        if(*str == '-') {
            const uint64_t max = strtoul(str + 1, &str, 10);
            ranges.push_back({ val, max });

            if(str[1] == '\n') {
                // merging reduces search size so makes it faster
                mergeRanges(ranges);
            }

            continue;
        }

        for(const Range& range : ranges) {
            if(val >= range.min && val <= range.max) {
                aSolution++;
                break;
            }
        }
    }
}

void Day5::partB() {
    std::vector<Range> ranges;
    // assume input is valid
    for(char* str = const_cast<char*>(input.c_str()); str[1] != '\n';) {
        const uint64_t min = strtoul(str, &str, 10);
        const uint64_t max = strtoul(str + 1, &str, 10);
        ranges.push_back({ min, max });
    }

    std::sort(ranges.begin(), ranges.end());
    for(auto it = ranges.begin(); it != ranges.end();) {
        Range& a = *it;

        for(it = it + 1; it != ranges.end(); it++) {
            const Range& b = *it;
            if(b.min > a.max) {
                break;
            }
            else if(b.max > a.max) {
                a.max = b.max;
            }
        }

        bSolution += (a.max - a.min) + 1;
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