#include "utils/StringUtils.hpp"
#include <Input.hpp>
#include <string>
#include <vector>

void AOCUtil::Input::clearCaches() {
    this->splitCaches = {};
}

std::vector<std::string>& AOCUtil::Input::getSplitText(std::string delim) {
    auto it = this->splitCaches.find(delim);
    if(it != this->splitCaches.end()) {
        return it->second;
    }

    std::vector<std::string>& out = this->splitCaches[delim];
    out = split(this->text, delim);
    return out;
}