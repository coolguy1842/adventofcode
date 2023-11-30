#ifndef __STRING_UTIL_HPP__
#define __STRING_UTIL_HPP__

#include <vector>
#include <string>
#include <string.h>

std::vector<std::string> split(std::string& str, char delim) {
    std::vector<std::string> out;
    std::string substr;

    for(char& c : str) {
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

std::vector<std::string> split(std::string str, std::string delim) {
    std::vector<std::string> out;
    std::string substr;

    size_t pos = 0;
    
    while((pos = str.find(delim)) != std::string::npos) {
        out.push_back(str.substr(0, pos));
        
        str.erase(0, pos + delim.length());
    }

    out.push_back(str);

    return out;
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