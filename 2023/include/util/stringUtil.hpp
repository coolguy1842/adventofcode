#ifndef __STRING_UTIL_HPP__
#define __STRING_UTIL_HPP__

#include <vector>
#include <string>
#include <string.h>

std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> out;
    std::string substr;

    for(const char& c : str) {
        if(c == delim) {
            out.push_back(substr);
            substr.clear();

            continue;
        }
        
        substr += c;
    }

    out.push_back(substr);

    return out;
}

std::vector<std::string> split(const std::string& str, std::string delim) {
    std::vector<std::string> result;

    size_t start = 0;
    size_t end = str.find(delim);
    while(end != std::string::npos) {
        auto sub = str.substr(start, end - start);
        result.push_back(sub);

        start = end + delim.length();
        end = str.find(delim, start);
    }

    auto sub = str.substr(start, end - start);
    result.push_back(sub);

    return result;
}

std::string replace(std::string str, std::string find, std::string replace) {
    if(find.empty()) return str;

    size_t i = 0;
    while((i = str.find(find, i)) != std::string::npos) {
        str.replace(i, find.length(), replace);
        i += replace.length();
    }

    return str;
}

int strtoint(const char* str) {
    int out = 0;
    bool neg = false;

    if(*str == '-') {
        neg = true;
        str++;
    }

    switch (neg) {
    case true:
        while(*str) {
            out = out * 10 - (*str++ - '0');
        }
        break;
    default:
        while(*str) {
            out = out * 10 + (*str++ - '0');
        }
        break;
    }

    return out;
}

long long strtoll(const char* str) {
    long long out = 0;
    bool neg = false;

    if(*str == '-') {
        neg = true;
        str++;
    }

    switch (neg) {
    case true:
        while(*str) {
            out = out * 10 - (*str++ - '0');
        }
        break;
    default:
        while(*str) {
            out = out * 10 + (*str++ - '0');
        }
        break;
    }

    return out;
}

size_t strtoull(const char* str) {
    size_t out = 0;

    while(*str) {
        out = out * 10 + (*str++ - '0');
    }

    return out;
}

#endif