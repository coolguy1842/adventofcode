#ifndef __COORDINATES_HPP__
#define __COORDINATES_HPP__

#include <utility>
#include <cstddef>

struct pair_hash {
    inline std::size_t operator()(const std::pair<std::size_t, std::size_t>& c) const {
        return (c.first << 32) + c.second;
    }

    inline std::size_t operator()(const std::pair<char, char>& c) const {
        return (c.first << 8) + c.second;
    }
};

#endif