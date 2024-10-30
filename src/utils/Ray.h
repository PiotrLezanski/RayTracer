#pragma once
#include "Vec3.h"

using Point3d = Vec3<double>;
using vec3 = Vec3<double>;

// Ray is basically a function P(t) = A + tb. A is a ray origin and B is the ray direction.
// P(t) is a 3D position along a line in 3D, with t as parameter. 
// T > 0 means moving into B direction. Negative mean moving into opposite.
class Ray
{
public:
	Ray() {}
	Ray(const Point3d& origin, const vec3& dir)
		: m_origin(origin), m_dir(dir) {}

	Point3d at(double t) { return m_origin + t * m_dir; }

	const Point3d& getOrigin() const { return m_origin; }
	const vec3& getDirection() const { return m_dir; }
private:
	Point3d m_origin;
	vec3 m_dir;
};
