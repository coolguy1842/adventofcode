#ifndef __RANGE_HPP__
#define __RANGE_HPP__

template <typename T, typename U = T, typename V = T>
class range {
    using value_type = decltype(T{} + U{} + V{});

public:
        range(T from, U to, V step = 1) : m_from{from}, m_to{to}, m_step{step} {}

        range(T to) : range{T{}, to} {}

        class iter {
public:
                iter(value_type pos, value_type step) : m_pos{pos}, m_step{step} {}

                iter& operator++() { m_pos += m_step; return *this; }
                value_type operator*() { return m_pos; }
                bool operator!=(const iter& other) { return m_pos*m_step < other.m_pos*m_step; }

private:
                value_type m_pos;
                value_type m_step;
        };

        iter begin() { return iter{m_from, m_step}; }
        iter end() { return iter{m_to, m_step}; }

private:
        value_type m_from;
        value_type m_to;
        value_type m_step;
};

#endif