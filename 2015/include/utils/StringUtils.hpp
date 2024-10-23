#ifndef __STRING_UTILS_HPP__
#define __STRING_UTILS_HPP__

#include <cmath>
#include <spdlog/spdlog.h>
#include <type_traits>

#include <vector>
#include <string>

namespace AOCUtil {

std::vector<std::string> split(std::string str, std::string delim);
std::string replace(std::string str, std::string find, std::string replace);

// templates dont like being in source files
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T strtonumeric(const char* str) {
    bool negative = *str == '-';
    T out = 0;

    if(negative) str++;
    while(*str) {
        out = out * 10 + (*str++ - '0');
    }
    
    return negative ? -out : out;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
int numerictostr(T number, char* out) {
    int numLen = std::max(0, (int)std::log10(number));

    size_t i = 0;
    do {
        out[numLen - i++] = (number % 10) + '0';
    } while((number /= 10));

    out[numLen + 1] = '\0';
    return numLen + 1;
}

};

#endif