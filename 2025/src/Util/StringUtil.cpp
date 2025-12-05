#include <Util/StringUtil.hpp>
#include <cstring>

void StringUtil::split(const std::string_view& str, const char& delim, std::function<void(const std::string&)> callback, bool includeEmpty) {
    if(callback == nullptr) {
        return;
    }

    const char* cur = str.data();
    do {
        const char* next = strchrnul(cur, delim);
        size_t len       = next - cur;

        if(includeEmpty || len != 0) {
            callback(std::string(cur, len));
        }

        cur = next;
    } while(*cur++);
}

void StringUtil::split(const std::string_view& str, const std::string_view& delim, std::function<void(const std::string&)> callback, bool includeEmpty) {
    if(callback == nullptr) {
        return;
    }

    const char* cur = str.data();
    do {
        const char* next = strstr(cur, delim.data());
        size_t len       = next != NULL ? (next - cur) : strlen(cur);

        if(includeEmpty || len != 0) {
            callback(std::string(cur, len));
        }

        cur = next;
    } while(cur++ != NULL);
}

std::vector<std::string> StringUtil::split(const std::string_view& str, const char& delim, bool includeEmpty) {
    std::vector<std::string> out;
    split(str, delim, [&out](const std::string& splitStr) { out.push_back(splitStr); }, includeEmpty);
    return out;
}

std::vector<std::string> StringUtil::split(const std::string_view& str, const std::string_view& delim, bool includeEmpty) {
    std::vector<std::string> out;
    split(str, delim, [&out](const std::string& splitStr) { out.push_back(splitStr); }, includeEmpty);
    return out;
}