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

    void MD5Hash(const char* str, char* out) {
        unsigned char digest[EVP_MAX_MD_SIZE];

        // deprecated but runs faster
        MD5_CTX ctx;
        MD5_Init(&ctx);
        MD5_Update(&ctx, str, strlen(str));
        MD5_Final(digest, &ctx);

        const char* hexDigits = "0123456789ABCDEF";
        for(size_t i = 0, j = 0; i < 3; i++) {
            out[j++] = hexDigits[(digest[i] >> 4) & 0x0F];
            out[j++] = hexDigits[digest[i] & 0xF];
        }
    }

    size_t partFunc(size_t numZeroes) {
        char str[64], hex[7];
        memset(str, '\0', sizeof(str));
        strcpy(str, input.text.c_str());

        char resStr[numZeroes];
        memset(resStr, '0', numZeroes);

        char* numPtr = str + input.text.size();
        for(size_t i = 0; ; i++) {
            AOCUtil::numerictostr(i, numPtr);
            MD5Hash(str, hex);

            hex[numZeroes] = '\0';
            if(strcmp(hex, resStr) == 0) {
                return i;
            }
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