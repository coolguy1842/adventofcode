#include <cstdio>
#include <spdlog/spdlog.h>
#include <utils/StringUtils.hpp>

#include <cstdlib>
#include <string>

#include <string.h>


std::vector<std::string> AOCUtil::split(std::string str, std::string delim) {
    std::vector<std::string> out;

    const char* delimPtr = delim.c_str();

    char temp[str.size() + 1];
    memcpy(temp, str.c_str(), str.size());

    char* res = strtok(temp, delimPtr);
    while(res != nullptr) {
        out.push_back(std::string(res));
        res = strtok(nullptr, delimPtr);
    }

    return out;
}


std::string AOCUtil::replace(std::string str, std::string find, std::string replace) {
    if(find.empty()) return str;

    size_t i = 0;
    while((i = str.find(find, i)) != std::string::npos) {
        str.replace(i, find.length(), replace);
        i += replace.length();
    }

    return str;
}