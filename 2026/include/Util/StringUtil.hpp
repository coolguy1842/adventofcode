#ifndef __STRING_UTIL_HPP__
#define __STRING_UTIL_HPP__

#include <functional>
#include <string>
#include <vector>

namespace StringUtil {

void split(const std::string& str, const char& delim, const std::function<void(const std::string&)>& callback, bool includeEmpty = false);
void split(const std::string& str, const std::string& delim, const std::function<void(const std::string&)>& callback, bool includeEmpty = false);

std::vector<std::string> split(const std::string& str, const char& delim, bool includeEmpty = false);
std::vector<std::string> split(const std::string& str, const std::string& delim, bool includeEmpty = false);

}; // namespace StringUtil

#endif