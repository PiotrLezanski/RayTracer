#pragma once

#include "../utils/utils.h"
#include "../utils/Ray.h"

class Sphere
{
public:
	Sphere(Point3d center, double radius);

	// checks if this sphere can be hit by given Ray
	bool isHittableBy(const Ray& ray);

	[[nodiscard]] const Point3d& getCenter() const { return m_center; }
	[[nodiscard]] const double& getRadius() const { return m_radius; }

private:
	Point3d m_center;
	double m_radius;
};