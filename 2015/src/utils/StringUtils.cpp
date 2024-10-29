#include <cstdio>
#include <spdlog/spdlog.h>
#include <utils/StringUtils.hpp>

#include <cstdlib>
#include <string>

#include <string.h>


std::vector<std::string> AOCUtil::split(std::string str, std::string delim) {
    std::vector<std::string> out;

    const char* delimPtr = delim.c_str();

    char* copy = strdup(str.c_str()), *token;
    while((token = strsep(&copy, delimPtr)) != NULL) {
        out.push_back(std::string(token));
    }

    free(copy);
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