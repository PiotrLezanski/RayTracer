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

// Return types
enum class Err
{
    ERROR = 0,
    SUCCESS
};

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

// Returns a random double between [min,max).
inline double randomDouble(double min, double max)
{
    return min + (max - min) * randomDouble();
}

// Converts a linear color value to a gamma-corrected value.
inline double linearToGamma(double linear)
{
    if (linear <= 0)
        return 0;

    return std::sqrt(linear);
}

// Vector utility functions
inline Vec randomVector()
{
    return Vec(randomDouble(), randomDouble(), randomDouble());
}

// Vector utility functions
inline Vec randomVector(double min, double max)
{
    return Vec(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

// Generates a random vector on the surface of a unit sphere (magnitude 1)
inline Vec randomUnitVec()
{
    while (true) 
    {
        Vec vec = randomVector(-1, 1);
        if (vec.length() >= 1)
            continue;
        return vec;
    }
}

// Generates a random vector uniformly distributed on the hemisphere
// defined by the given normal vector.
inline Vec randomVectorOnHemisphere(const Vec& normal)
{
    Vec unitVec = randomUnitVec();
    // Check if unit vector is in the same hemisphere as the normal
    if (dot_product(unitVec, normal) > 0.0)
        return unitVec;
    else
        return -unitVec;
}

// Calculates the reflection of a vector "vec" off a surface defined by its normal vector "normal".
// This formula ensures that the incoming vector is reflected symmetrically across the plane.
// The result is a new vector pointing in the direction of the reflection, maintaining the 
// law of reflection: the angle of incidence equals the angle of reflection.
//             ^ normal
//             |   
//   incoming  |   reflected
//   vector    |   vector
//       \     |     /
//        \    |    /
//         \   |   /
//          \  |  /
//           \ | /
//            \|/
//  -----------*-------------> Surface
//           point (point of reflection)
inline Vec reflect(const Vec& vec, const Vec& normal)
{
    return vec - 2 * dot_product(vec, normal) * normal;
}