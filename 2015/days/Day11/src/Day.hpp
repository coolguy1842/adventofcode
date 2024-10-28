#ifndef __DAY_HPP__
#define __DAY_HPP__

#include "utils/Range.hpp"
#include <IDay.hpp>
#include <spdlog/spdlog.h>
#include <string>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    std::string aSolution;
    std::string bSolution;

    bool hasIncrementing(std::string& line) {
        for(size_t i : AOCUtil::Range(line.size() - 2)) {
            char& lHS = line[i];
            char& mHS = line[i + 1];
            char& rHS = line[i + 2];
            
            if(lHS == mHS - 1 && mHS == rHS - 1) {
                return true;
            }
        }

        return false;
    }

    bool hasDouble(std::string& line) {
        for(size_t i : AOCUtil::Range(line.size() - 2)) {
            char& lHS = line[i];
            char& rHS = line[i + 1];
            
            if(lHS != rHS) {
                continue;
            }

            for(size_t j : AOCUtil::Range(i + 1, line.size() - 1)) {
                char& lHS2 = line[j];
                char& rHS2 = line[j + 1];
                
                if(lHS2 != rHS2 || lHS == lHS2) {
                    continue;
                }

                return true;
            }

            // wont have any other pairs
            break;
        }

        return false;
    }

    bool isInvalid(char& c) {
        switch(c) {
        case 'i': case 'o': case 'l': return true;
        default: return false;
        }
    }

    bool hasInvalid(std::string& line) {
        char* strPtr = (char*)line.c_str();
        while(*strPtr) {
            if(isInvalid(*strPtr++)) {
                return true;
            }
        }

        return false;
    }



    std::string partFunc(std::string password) {
        size_t runs = 0;
        while(true) {
            if(runs++ > 0 && hasIncrementing(password) && hasDouble(password) && !hasInvalid(password)) {
                break;
            }

            for(size_t i = password.size() - 1; i > 0; i--) {
                char& cur = password[i];
                if(cur >= 'z') {
                    cur = 'a';
                    continue;
                }
                
                cur++;
                if(isInvalid(cur)) {
                    cur++;
                }

                break;
            }
        }

        return password;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH) {}

    void partA() {
        aSolution = partFunc(input.text);
    }

    void partB() {
        // must do part a
        if(aSolution.size() <= 0) {
            partA();
        }

        bSolution = partFunc(aSolution);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aSolution);
        if(partB) spdlog::info("Part B: {}", bSolution);
    }
};

#endif