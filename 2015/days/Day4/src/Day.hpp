#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <cmath>
#include <utils/Range.hpp>
#include <utils/StringUtils.hpp>

#include <IDay.hpp>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <optional>
#include <spdlog/spdlog.h>

#include <openssl/evp.h>
#include <openssl/md5.h>
#include <string>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    std::optional<size_t> aKeyNumber;
    std::optional<size_t> bKeyNumber;

    void incrementStrNumber(char* numStr, size_t& numLen) {
        for(size_t i = numLen - 1; i >= 0; i--) {
            char& digit = ++numStr[i];
            
            switch(digit) {
            case '9' + 1:
                if(i == 0) {
                    // move all digits back
                    digit = '1';
                    numStr[i += 2] = '0';

                    for(; i < numLen - 1; i += 2) {
                        std::swap(numStr[i], numStr[i + 1]);
                    }

                    numStr[numLen++] = '0';
                    return;
                }

                digit = '0';
                break;
            default: return;
            }
        }
    }

    size_t partFunc(int numZeroes) {
        size_t strLen = input.text.size();

        unsigned char digest[EVP_MAX_MD_SIZE], str[64], *byte = digest;
        memcpy(str, input.text.c_str(), input.text.size());
        memset(str + input.text.size(), '\0', sizeof(str) - input.text.size());

        char* numPtr = (char*)str + strLen;
        *numPtr = '0' - 1;
        
        size_t numLen = 1;
        for(size_t i = 0; ; i++) {
            byte = digest;
            
            incrementStrNumber(numPtr, numLen);

            // deprecated but its faster than the EVP_Digest functions so who cares
            MD5(str, strLen + numLen, digest);

            if(numZeroes % 2 == 0) {
                for(int j = 0; j < numZeroes; j += 2) {
                    if(*byte++) {
                        goto pass;
                    }
                }
            }
            else {
                bool leastSignificant = false;
                for(int j = 0; j < numZeroes; j++, leastSignificant = !leastSignificant) {
                    if((leastSignificant ? *byte++ : *byte >> 4) & 0x0F) {
                        goto pass;
                    }
                }
            }

            return i;
            pass:
        }
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aKeyNumber(std::nullopt), bKeyNumber(std::nullopt) {}

    void partA() {
        aKeyNumber = partFunc(5);
    }
    
    void partB() {
        bKeyNumber = partFunc(6);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aKeyNumber.value());
        if(partB) spdlog::info("Part B: {}", bKeyNumber.value());
    }
};

#endif