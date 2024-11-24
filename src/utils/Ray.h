#pragma once

#include "utils.h"

class Hittable;

// Ray is basically a function P(t) = A + tB. A is a ray origin and B is the ray direction.
// P(t) is a 3D position along a line in 3D, with t as parameter. 
// T > 0 means moving into B direction. Negative mean moving into opposite.
class Ray
{
public:
	Ray() {}
	Ray(const Point3d& origin, const Vec& dir)
		: m_origin(origin), m_dir(dir) {}

	Point3d at(double t) const { return m_origin + t * m_dir; }

	// Calculate color of the pixel in the scene that Ray hit
	Color calculateColor(const Hittable& scene) const;

	const Point3d& getOrigin() const { return m_origin; }
	const Vec& getDirection() const { return m_dir; }
private:
	Point3d m_origin;
	Vec m_dir;
};