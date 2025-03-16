#pragma once

#include "utils.h"

struct Interval 
{
    // Default interval is empty
    Interval() : m_min(+INF), m_max(-INF) {}
    Interval(double min, double max) : m_min(min), m_max(max) {}

    double size() const { return m_max - m_min; }
    bool contains(double x) const { return m_min <= x && x <= m_max; }
    bool surrounds(double x) const { return m_min < x && x < m_max; }
    void addPadding(double);

    double m_min;
    double m_max;
};

void Interval::addPadding(double p)
{
    const double padding = p / 2;
    m_min -= padding;
    m_max += padding;
}

inline const Interval EMPTY_INTERVAL = Interval(+INF, -INF);
inline const Interval UNIVERSE_INTERVAL = Interval(-INF, +INF);
