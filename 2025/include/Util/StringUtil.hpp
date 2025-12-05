#ifndef __STRING_UTIL_HPP__
#define __STRING_UTIL_HPP__

#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace StringUtil {

void split(const std::string_view& str, const char& delim, std::function<void(const std::string&)> callback, bool includeEmpty = false);
void split(const std::string_view& str, const std::string_view& delim, std::function<void(const std::string&)> callback, bool includeEmpty = false);

std::vector<std::string> split(const std::string_view& str, const char& delim, bool includeEmpty = false);
std::vector<std::string> split(const std::string_view& str, const std::string_view& delim, bool includeEmpty = false);

}; // namespace StringUtil

#endif