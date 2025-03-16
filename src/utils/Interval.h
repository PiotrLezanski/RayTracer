#pragma once

#include "utils.h"

struct Interval 
{
    // Default interval is empty
    Interval() : m_min(+INF), m_max(-INF) {}
    Interval(double min, double max) : m_min(min), m_max(max) {}
    Interval(const Interval& a, const Interval& b);

    double size() const { return m_max - m_min; }
    bool contains(double x) const { return m_min <= x && x <= m_max; }
    bool surrounds(double x) const { return m_min < x && x < m_max; }
    void addPadding(double);

    double m_min;
    double m_max;
};

inline Interval::Interval(const Interval& a, const Interval& b)
{
    m_min = std::min(a.m_min, b.m_min);
    m_max = std::max(b.m_max, b.m_max);
}

inline void Interval::addPadding(double p)
{
    const double padding = p / 2;
    m_min -= padding;
    m_max += padding;
}

inline const Interval EMPTY_INTERVAL = Interval(+INF, -INF);
inline const Interval UNIVERSE_INTERVAL = Interval(-INF, +INF);
