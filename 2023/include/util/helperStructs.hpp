#ifndef __HELPER_STRUCTS_HPP__
#define __HELPER_STRUCTS_HPP__

struct Coordinates {
    long x;
    long y;
};

bool operator==(const Coordinates& a, const Coordinates& b) {
    return a.x == b.x && a.y == b.y; 
}

struct coordinates_hash {
    inline std::size_t operator()(const Coordinates& c) const {
        return ((size_t)c.x << 32) + c.y;
    }
};

#endif