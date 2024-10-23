#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <utils/Hashes.hpp>

#include <cstring>
#include <string>
#include <unordered_set>
#include <utility>
#include <utils/Range.hpp>

#include <IDay.hpp>
#include <spdlog/spdlog.h>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    size_t aNiceStrings;
    size_t bNiceStrings;

    bool isVowel(char c) {
        switch(c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default: return false;
        }
    }

    bool isDisallowed(char prev, char current) {
        const char* disallowed[] = {
            "ab",
            "cd",
            "pq",
            "xy"
        };

        switch(prev) {
        case 'a': case 'c': case 'p': case 'x': break;
        default: return false;
        }
        
        switch(current) {
        case 'b': case 'd': case 'q': case 'y': break;
        default: return false;
        }

        for(const char* check : disallowed) {
            if(check[0] == prev && check[1] == current) {
                return true;
            }
        }

        return false;
    }


    bool isNiceA(std::string& line) {
        size_t vowels = 0;
        size_t doubles = 0;

        for(size_t i : AOCUtil::Range(line.size())) {
            char& prev = i > 0 ? line[i - 1] : line[line.size()];
            char& cur = line[i];

            if(isVowel(cur)) {
                vowels++;
            }

            if(isDisallowed(prev, cur)) {
                return false;
            }

            if(prev == cur) {
                doubles++;
            }
        }

        return vowels >= 3 && doubles >= 1;
    }

    bool isNiceB(std::string& line) {
        bool hasPair = false;
        bool hasDouble = false;
        
        std::unordered_set<std::pair<char, char>, pair_hash> pairs;
        for(size_t i : AOCUtil::Range(line.size() - 1)) {
            char& prev = i > 0 ? line[i - 1] : line[line.size()];
            char& cur = line[i];
            char& next = line[i + 1];

            if(!hasDouble && prev == next) {
                hasDouble = true;
            }

            if(!hasPair) {
                char find[] = { cur, next };
                size_t pos = line.find(find);
                
                if(pos == std::string::npos) {
                    continue;    
                }

                size_t pos2 = line.find(find, pos + 1);
                while(pos2 != std::string::npos) {
                    if(pos != pos2 && pos2 - pos > 1) {
                        hasPair = true;

                        break;
                    }

                    pos2 = line.find(find, pos2 + 1);
                }
            }

            if(hasDouble && hasPair) {
                break;
            }
        }

        return hasDouble && hasPair;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aNiceStrings(0), bNiceStrings(0) {}

    void partA() {
        for(std::string& line : input.getSplitText("\n")) {
            if(isNiceA(line)) {
                aNiceStrings++;
            }
        }
    }

    void partB() {
        for(std::string& line : input.getSplitText("\n")) {
            if(isNiceB(line)) {
                bNiceStrings++;
            }
        }
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aNiceStrings);
        if(partB) spdlog::info("Part B: {}", bNiceStrings);
    }
};

#endif