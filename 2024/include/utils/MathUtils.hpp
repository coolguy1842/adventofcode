#ifndef __MATH_UTILS_HPP__
#define __MATH_UTILS_HPP__

#include <cstddef>
#include <type_traits>

template<int E, int N>
struct _powS {
    enum { value = E * _powS<E, N - 1>::value };
};

template <int E>
struct _powS<E, 0> {
    enum { value = 1 };
};

// from https://stackoverflow.com/a/18596077
template<int E, typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T quick_pow(T n) {
    static T lookupTable[] = {
        _powS<E, 0>::value, _powS<E, 1>::value, _powS<E, 2>::value,
        _powS<E, 3>::value, _powS<E, 4>::value, _powS<E, 5>::value,
        _powS<E, 6>::value, _powS<E, 7>::value, _powS<E, 8>::value,
        _powS<E, 9>::value
    };

    return lookupTable[n];
}


inline size_t baseTwoDigits(const size_t& x) {
    return x ? 32 - __builtin_clz(x) : 0;
}

// from https://stackoverflow.com/a/25934909
inline size_t quick_log10(const size_t& x) {
    static const unsigned char guess[33] = {
        0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
        9, 9, 9
    };

    static const size_t tenToThe[] = {
        1, 10, 100, 1000, 10000, 100000, 
        1000000, 10000000, 100000000, 1000000000,
    };
    
    size_t digits = guess[baseTwoDigits(x)];
    return digits + (x >= tenToThe[digits]);
}

#endif