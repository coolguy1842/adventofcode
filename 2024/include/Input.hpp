#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include <strutils.hpp>

#include <unordered_map>
#include <string>
#include <vector>

namespace AOCUtil {
    
struct Input {
private:
    std::unordered_map<std::string, std::vector<std::string>> splitCaches;

public:
    Input(std::string text) : text(text) {}
    Input() : text("") {}

    std::string text;
    
    // use if text is modified
    void clearCaches();
    std::vector<std::string>& getSplitText(std::string delim);
};

};

#endif