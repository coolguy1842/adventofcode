#ifndef __DAY_HPP__
#define __DAY_HPP__

#include "utils/StringUtils.hpp"
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

    size_t partFunc(size_t numZeroes) {
        size_t strLen = input.text.size();

        unsigned char digest[EVP_MAX_MD_SIZE], *byte = digest;
        char str[64];

        memset(str, '\0', sizeof(str));
        strcpy(str, input.text.c_str());

        char* numPtr = str + strLen;
        for(size_t i = 0; ; i++) {
            byte = digest;
            
            size_t numLen = AOCUtil::numerictostr(i, numPtr);
            MD5((unsigned char*)str, strLen + numLen, digest);

            if(numZeroes % 2 == 0) {
                for(size_t j = 0; j < numZeroes; j += 2) {
                    if(*byte++) {
                        goto pass;
                    }
                }
            }
            else {
                for(size_t j = 0; j < numZeroes; j++) {
                    if((j % 2 == 0 ? *byte >> 4 : *byte++) & 0x0F) {
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