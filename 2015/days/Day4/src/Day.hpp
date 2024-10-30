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
    typedef bool(*checkFunc)(unsigned char*);

    std::optional<size_t> aKeyNumber;
    std::optional<size_t> bKeyNumber;

    void incrementStrNumber(unsigned char* numStr, size_t& numLen) {
        for(size_t i = numLen - 1; i >= 0; i--) {
            unsigned char& digit = numStr[i];
            
            switch(digit) {
            case '9':
                digit = '0';
                if(i != 0) {
                    goto pass;
                }

                *(numStr + 1) = '0';
                *(numStr + numLen++) = '0';
            default: digit++; return;
            }

            pass:
        }
    }

    inline static bool checkDigestA(unsigned char* digest) { return !(digest[0] || digest[1] || digest[2] & 0xF0);}
    inline static bool checkDigestB(unsigned char* digest) { return !(digest[0] || digest[1] || digest[2]); }

    size_t partFunc(const bool& partB = false) {
        #define STR_LEN 64
        #define HASHED_LEN 16
        
        const size_t& strLen = input.text.size();
        const checkFunc& func = partB ? checkDigestB : checkDigestA;

        unsigned char *str = (unsigned char*)malloc(STR_LEN), *numPtr = str + strLen, *digest = str + (STR_LEN - HASHED_LEN);
        memcpy(str, input.text.c_str(), strLen);

        *numPtr = '0';

        for(size_t i = 0, numLen = 1; ; i++) {
            MD5(str, strLen + numLen, digest);
            if(func(digest)) {
                free(str);
                return i;
            }

            incrementStrNumber(numPtr, numLen);
        }
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aKeyNumber(std::nullopt), bKeyNumber(std::nullopt) {}

    void partA() {
        aKeyNumber = partFunc();
    }
    
    void partB() {
        bKeyNumber = partFunc(true);
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) spdlog::info("Part A: {}", aKeyNumber.value());
        if(partB) spdlog::info("Part B: {}", bKeyNumber.value());
    }
};

#endif