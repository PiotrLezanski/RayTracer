#pragma once

// Common headers
#include "Vec3.h"

#include <memory>
#include <vector>
#include <random>
#include <string>

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

// Renderer constants
const int DEFAULT_SAMPLES_PER_PIXEL = 10;
const int DEFAULT_MAX_RECURSION_DEPTH = 10;

// Camera view contants
const int32 RENDERED_IMAGE_HEIGHT = 256;
const double DEFAULT_FIELD_OF_VIEW = 20;
const Point3d DEFAULT_CAMERA_LOOK_FROM = Point3d(13, 2, 3);
const Point3d DEFAULT_CAMERA_LOOK_AT = Point3d(0, 0, 0);

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

inline int randomInt(int min, int max) {
    // Returns a random integer in [min,max].
    return int(randomDouble(min, max + 1));
}

// Converts a linear color value to a gamma-corrected value.
inline double linearToGamma(double linear)
{
    if (linear <= 0)
        return 0;

    return std::sqrt(linear);
}

inline void linearToGamma(Color& color)
{
    color[0] = linearToGamma(color[0]);
    color[1] = linearToGamma(color[1]);
    color[2] = linearToGamma(color[2]);
}

// Format large integers
// e.g. 12312343 -> 12,312,343 
inline std::string formatLargeIntegers(unsigned long value)
{
	std::string num = std::to_string(value);
    std::string result;

    size_t counter = -1;
    for(int i = num.size()-1; i>=0; --i)
    {
        ++counter;
        if (counter % 3 == 0 && counter != 0)
            result.push_back(',');

        result.push_back(num[i]);
    }
    std::reverse(result.begin(), result.end());

    return result;
}

// Vector utility functions
inline Vec randomVector()
{
    return Vec(randomDouble(), randomDouble(), randomDouble());
}

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

// This function calculates the refraction vector given an incident vector (uv),
// a surface normal (n), and the ratio of refractive indices
inline Vec refract(const Vec& uv, const Vec& n, double refractionRatio)
{
    // Compute the cosine of the angle between the incident vector and the normal.
    double cos_theta = std::fmin(dot_product(-uv, n), 1.0);

    Vec outPerpendicular = refractionRatio * (uv + cos_theta * n);
    Vec outParallel = -std::sqrt(std::fabs(1.0 - outPerpendicular.cords_squared())) * n;

    // Return the sum of the perpendicular and parallel components,
    // which gives the final refracted vector
    return outPerpendicular + outParallel;
}

// Calculates the reflectance of light at the interface between two media with different
// refractive indices using Schlick's approximation. Reflectance determines how much
// light is reflected versus refracted at the boundary.
// This is useful in for simulating realistic light interactions with surfaces like glass or water.
// "cosine" - The cosine of the angle between the incident ray and the surface normal.
// "refractionIndex" - The refractive index of the material being entered.
// Return - The reflectance value (between 0 and 1), indicating the fraction of light reflected.
inline double reflectance(double cos, double refractionIndex)
{
    double r0 = (1 - refractionIndex) / (1 + refractionIndex);
    r0 = std::pow(r0, 2);
    return r0 + (1 - r0) * std::pow((1 - cos), 5);
}