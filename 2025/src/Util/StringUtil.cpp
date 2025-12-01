#include <Util/StringUtil.hpp>
#include <cstddef>
#include <cstring>
#include <string>
#include <vector>

std::vector<std::string> StringUtil::split(const std::string& str, const std::string& delim) {
    const char *base = str.c_str(), *cur = base;

    std::vector<std::string> out;
    while(cur != NULL) {
        const char* next = strstr(cur, delim.c_str());

        size_t len = next != NULL ? (next - cur) : strlen(cur);
        if(len != 0) {
            out.push_back(std::string(cur, len));
        }

        cur = next + (next != NULL);
    }

    return out;
}

void StringUtil::split(const std::string& str, const std::string& delim, std::function<void(const std::string&)> callback) {
    if(callback == nullptr) {
        return;
    }

    const char *base = str.c_str(), *cur = base;

    while(cur != NULL) {
        const char* next = strstr(cur, delim.c_str());

        size_t len = next != NULL ? (next - cur) : strlen(cur);
        if(len != 0) {
            callback(std::string(cur, len));
        }

        cur = next + (next != NULL);
    }
}