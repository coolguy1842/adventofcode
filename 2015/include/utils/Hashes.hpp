#ifndef __COORDINATES_HPP__
#define __COORDINATES_HPP__

#include <functional>
#include <glm/glm.hpp>

#include <utility>
#include <cstddef>

struct pair_hash {
    inline std::size_t operator()(const std::pair<std::size_t, std::size_t>& c) const {
        return (c.first << 32) + c.second;
    }
};

struct glm_hash {
    inline size_t operator()(const glm::ivec2& k) const {
        return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
    }

    inline bool operator()(const glm::ivec2& a, const glm::ivec2& b) const {
        return a.x == b.x && a.y == b.y;
    }
};

#endif