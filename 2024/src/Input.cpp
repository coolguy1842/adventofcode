#include <Input.hpp>

void AOCUtil::Input::clearCaches() {
    this->splitCaches = {};
}

std::vector<std::string>& AOCUtil::Input::getSplitText(std::string delim) {
    auto it = this->splitCaches.find(delim);
    if(it != this->splitCaches.end()) {
        return it->second;
    }

    this->splitCaches[delim] = split(this->text, delim);
    return this->splitCaches[delim];
}