#include <Util/StringUtil.hpp>
#include <cstring>

void StringUtil::split(const std::string& str, const char& delim, const std::function<void(const std::string&)>& callback, bool includeEmpty) {
    if(callback == nullptr) {
        return;
    }

    const char* cur = str.data();
    while(*cur != '\0') {
        const char* next = strchrnul(cur, delim);
        size_t len       = next - cur;

        if(includeEmpty || len != 0) {
            callback(std::string(cur, len));
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        cur = next + 1;
    };
}

void StringUtil::split(const std::string& str, const std::string& delim, const std::function<void(const std::string&)>& callback, bool includeEmpty) {
    if(callback == nullptr) {
        return;
    }

    const char* cur = str.data();
    while(*cur != '\0') {
        const char* next = strstr(cur, delim.c_str());
        size_t len       = next != nullptr ? (next - cur) : strlen(cur);

        if(includeEmpty || len != 0) {
            callback(std::string(cur, len));
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        cur = next + 1;
    };
}

std::vector<std::string> StringUtil::split(const std::string& str, const char& delim, bool includeEmpty) {
    std::vector<std::string> out;
    split(str, delim, [&out](const std::string& splitStr) { out.push_back(splitStr); }, includeEmpty);
    return out;
}

std::vector<std::string> StringUtil::split(const std::string& str, const std::string& delim, bool includeEmpty) {
    std::vector<std::string> out;
    split(str, delim, [&out](const std::string& splitStr) { out.push_back(splitStr); }, includeEmpty);
    return out;
}