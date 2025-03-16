#pragma once

#include "../../utils/Interval.h"
#include "../../utils/Ray.h"

// Axis-Aligned Bounding Box (AABB) class
// Simple and efficient bounding volume used in spatial computations.
// It's main purpose is for efficient ray-box intersection calculation for rendering acceleration.
// They are fundamental in BVH structures.
class BoundingBox
{
public:
	BoundingBox() {}
	BoundingBox(const Interval& x, const Interval& y, const Interval& z);
	// Create rectangular bounding box from two corner points
	BoundingBox(const Point3d& p1, const Point3d& p2);

	// 0 - x, 1 - y, 2<= - z
	const Interval& getIntervalFromAxis(int axis) const;

	// This method checks whether a ray intersects AABB by using slab method.
	// If the ray misses bounding box, we can skip expensive calculacions for objects inside.
	// Slab method repeatedly cuts portions of the ray with regard to every axis.
	// Ray intersects AAABB if there is some segment left.
	bool hit(const Ray& r, Interval ray_t);

private:
	Interval m_x;
	Interval m_y;
	Interval m_z;
};