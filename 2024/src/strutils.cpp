#include <cstdlib>
#include <string>
#include <strutils.hpp>

#include <string.h>

std::vector<std::string> AOCUtil::split(std::string str, std::string delim) {
    std::vector<std::string> out;

    const char* strPtr = str.c_str();
    const char* delimPtr = delim.c_str();

    char* temp = (char*)malloc(str.size() + 1);
    strcpy(temp, strPtr);

    char* res = strtok(temp, delimPtr);
    while(res != nullptr) {
        out.push_back(std::string(res));
        res = strtok(nullptr, delimPtr);
    }

    free(temp);
    return out;
}