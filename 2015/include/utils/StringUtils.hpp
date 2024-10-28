#ifndef __STRING_UTILS_HPP__
#define __STRING_UTILS_HPP__

#include <cmath>
#include <optional>
#include <spdlog/spdlog.h>
#include <type_traits>

#include <vector>
#include <string>

namespace AOCUtil {

std::vector<std::string> split(std::string str, std::string delim);
std::string replace(std::string str, std::string find, std::string replace);

// templates dont like being in source files
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
std::optional<T> strtonumeric(const char* str, bool failOnNonDigit) {
    bool negative = *str == '-';
    T out = 0;

    if(negative) str++;
    while(*str) {
        switch(*str) {
        case '0' ... '9': break;
        default:
            if(failOnNonDigit) return std::nullopt;
            return out;
        }
        
        out = out * 10 + (*str++ - '0');
    }
    
    return negative ? -out : out;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T strtonumeric(const char* str) {
    bool negative = *str == '-';
    T out = 0;

    if(negative) str++;
    while(*str) {
        switch(*str) {
        case '0' ... '9': break;
        default: return out;
        }
        
        out = out * 10 + (*str++ - '0');
    }
    
    return negative ? -out : out;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
int numerictostr(T number, char* out) {
    if(number <= 9) {
        *out = number + '0';
        *(out + 1) = '\0';

        return 1;
    }

    auto result = std::to_chars(out, out + 32, number);
    
    *result.ptr = '\0';
    return result.ptr - out;
}

};

#endif