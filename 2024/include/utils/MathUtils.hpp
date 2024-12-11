#ifndef __MATH_UTILS_HPP__
#define __MATH_UTILS_HPP__

#include <cstdint>
#include <type_traits>

template<uint64_t E, uint64_t N>
struct _powS {
    enum { value = E * _powS<E, N - 1>::value };
};

template<uint64_t E>
struct _powS<E, 0> {
    enum { value = 1 };
};

// from https://stackoverflow.com/a/18596077
// probably needs a signed version but I'll make that if I need it
template<uint64_t E, typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T quick_pow(T n) {
    constexpr static uint64_t powers[] = {
        _powS<E, 0>::value, _powS<E, 1>::value, _powS<E, 2>::value,
        _powS<E, 3>::value, _powS<E, 4>::value, _powS<E, 5>::value,
        _powS<E, 6>::value, _powS<E, 7>::value, _powS<E, 8>::value,
        _powS<E, 9>::value, _powS<E, 10>::value, _powS<E, 11>::value,
        _powS<E, 12>::value, _powS<E, 13>::value, _powS<E, 14>::value,
        _powS<E, 15>::value, _powS<E, 16>::value, _powS<E, 17>::value,
        _powS<E, 18>::value
    };

    return powers[n];
}

// from u/ednl https://www.reddit.com/r/adventofcode/comments/1hbm0al/comment/m1lilau, https://stackoverflow.com/a/25934909, http://coliru.stacked-crooked.com/a/16f8a901a31b9d73
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
uint8_t quick_log10(T num) {
    constexpr static uint8_t digits[] = {
        19, 18,18,18,18,  // index=0 (19/20 digits) unreachable for int64_t
        17,17,17, 16,16,16, 15,15,15,15,
        14,14,14, 13,13,13, 12,12,12,12,
        11,11,11, 10,10,10,  9, 9, 9, 9,
        8, 8, 8,  7, 7, 7,  6, 6, 6, 6,
        5, 5, 5,  4, 4, 4,  3, 3, 3, 3,
        2, 2, 2,  1, 1, 1,  0, 0, 0, 1 // index=64 for x=0 => 1 digit
    };

    const uint8_t approx = digits[num ? __builtin_clzll(num) : 64]; // clz undefined for x=0
    return approx + (num >= quick_pow<10, T>(approx));
}


#endif