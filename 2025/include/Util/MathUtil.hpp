#ifndef __MATH_UTILS_HPP__
#define __MATH_UTILS_HPP__

// from 2024

#include <cstdint>
#include <cstdio>
#include <type_traits>

namespace MathUtil {
template<uint64_t E, uint64_t N>
struct _pow {
    enum { value = E * _pow<E, N - 1>::value };
};

template<uint64_t E>
struct _pow<E, 0> {
    enum { value = 1 };
};

// from https://stackoverflow.com/a/18596077
template<uint64_t E, typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type, typename = typename std::enable_if<std::is_unsigned<T>::value, T>::type>
uint64_t quickPow(T n) {
    static uint64_t lookupTable[] = {
        _pow<E, 0>::value, _pow<E, 1>::value, _pow<E, 2>::value,
        _pow<E, 3>::value, _pow<E, 4>::value, _pow<E, 5>::value,
        _pow<E, 6>::value, _pow<E, 7>::value, _pow<E, 8>::value,
        _pow<E, 9>::value, _pow<E, 10>::value, _pow<E, 11>::value,
        _pow<E, 12>::value, _pow<E, 13>::value, _pow<E, 14>::value,
        _pow<E, 15>::value, _pow<E, 16>::value, _pow<E, 17>::value,
        _pow<E, 18>::value
    };

    return lookupTable[n];
}

// from u/ednl https://www.reddit.com/r/adventofcode/comments/1hbm0al/comment/m1lilau, https://stackoverflow.com/a/25934909, http://coliru.stacked-crooked.com/a/16f8a901a31b9d73
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
uint8_t quickLog10(T num) {
    constexpr static uint8_t digits[] = {
        19, 18, 18, 18, 18, // index=0 (19/20 digits) unreachable for int64_t
        17, 17, 17, 16, 16, 16, 15, 15, 15, 15,
        14, 14, 14, 13, 13, 13, 12, 12, 12, 12,
        11, 11, 11, 10, 10, 10, 9, 9, 9, 9,
        8, 8, 8, 7, 7, 7, 6, 6, 6, 6,
        5, 5, 5, 4, 4, 4, 3, 3, 3, 3,
        2, 2, 2, 1, 1, 1, 0, 0, 0, 1 // index=64 for x=0 => 1 digit
    };

    const uint8_t approx = digits[num ? __builtin_clzll(num) : 64]; // clz undefined for x=0
    return approx + (num >= quickPow<10>(approx));
}
}; // namespace MathUtil

#endif