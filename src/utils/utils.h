#pragma once

// Common headers
#include "Vec3.h"

#include <memory>
#include <vector>

// Custom types
using int32 = uint32_t;
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