#pragma once

// Common headers
#include "Vec3.h"

#include <memory>
#include <vector>
#include <random>

// Custom types
using int32 = uint32_t;

// NOTE: Color objects store normalized RGB values
// They are transformed into standard RGB when printed into PPM
using Color = Vec3<double>;

using Point3d = Vec3<double>;
using Vec = Vec3<double>;

// Constants
const inline Color DEFAULT_COLOR = Color(0, 0, 0);
const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Functions
inline double degreesToRadians(double degrees)
{
    return degrees * PI / 180.0;
}

// Random double between 0 and 1
inline double randomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}