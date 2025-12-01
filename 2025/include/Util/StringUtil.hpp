#ifndef __STRING_UTIL_HPP__
#define __STRING_UTIL_HPP__

#include <functional>
#include <string>
#include <vector>

namespace StringUtil {

std::vector<std::string> split(const std::string& str, const std::string& delim);
void split(const std::string& str, const std::string& delim, std::function<void(const std::string&)> callback);

}; // namespace StringUtil

#endif