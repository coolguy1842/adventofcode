#ifndef __RANGE_HPP__
#define __RANGE_HPP__

namespace AOCUtil {

template<typename T, typename U = T, typename V = T>
class Range {
private:
    using value_type = decltype(T() + U() + V());

    value_type _from;
    value_type _to;
    value_type _step;

public:
    class iter {
    private:
        value_type _pos;
        value_type _step;

    public:
        iter(value_type pos, value_type step) : _pos{pos}, _step{step} {}

        iter& operator++() { _pos += _step; return *this; }
        value_type operator*() { return _pos; }
        bool operator!=(const iter& other) { return _pos * _step < other._pos * _step; }
    };

    Range(T from, U to, V step = 1) : _from{from}, _to{to}, _step{step} {}
    Range(T to) : Range{T(), to} {}

    iter begin() { return iter(_from, _step); }
    iter end() { return iter(_to, _step); }
};

};

#endif