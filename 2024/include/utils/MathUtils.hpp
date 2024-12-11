#ifndef __MATH_UTILS_HPP__
#define __MATH_UTILS_HPP__

#include <cstddef>
#include <cstdint>
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


// inline uint64_t baseTwoDigits(const uint64_t& x) {
//     return x ? 32 - __builtin_clz(x) : 0;
// }

// inline uint64_t quick_log10(const uint64_t& x) {
//     static const unsigned char guess[33] = {
//         0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
//         3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
//         6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
//         9, 9, 9
//     };

//     static const uint64_t tenToThe[] = {
//         1, 10, 100, 1000, 10000, 100000, 
//         1000000, 10000000, 100000000, 1000000000,
//     };
    
//     uint64_t digits = guess[baseTwoDigits(x)];
//     return digits + (x >= tenToThe[digits]);
// }

// from https://stackoverflow.com/a/25934909, http://coliru.stacked-crooked.com/a/16f8a901a31b9d73
template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
uint8_t baseTwoDigits(T num) {
    size_t bytes = sizeof(num);
    
    return num ? (8 * bytes) - (bytes > 4 ? __builtin_clzll(num) : __builtin_clz(num)) : 0;
}

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
uint8_t quick_log10(T num) {
    if(num == 0) {
        return 0;
    }

    static constexpr T tenToThe[]= {
        T(1U), T(10U), T(100U), T(1000U), T(10000U), T(100000U), T(1000000U), T(10000000U), T(100000000U),
        T(1000000000U), T(10000000000U), T(100000000000U), T(1000000000000U), T(10000000000000U),
        T(100000000000000U), T(1000000000000000U), T(10000000000000000U), T(100000000000000000U),
        T(1000000000000000000U), T(10000000000000000000U),
    };
    
    static constexpr uint8_t guess[65]= {
        0 ,0 ,0 ,0 , 1 ,1 ,1 , 2 ,2 ,2 ,
        3 ,3 ,3 ,3 , 4 ,4 ,4 , 5 ,5 ,5 ,
        6 ,6 ,6 ,6 , 7 ,7 ,7 , 8 ,8 ,8 ,
        9 ,9 ,9 ,9 , 10,10,10, 11,11,11,
        12,12,12,12, 13,13,13, 14,14,14,
        15,15,15,15, 16,16,16, 17,17,17,
        18,18,18,18, 19
    };

    const uint8_t digits = guess[baseTwoDigits(num)];
    return digits + (num >= tenToThe[digits]);
}


#endif