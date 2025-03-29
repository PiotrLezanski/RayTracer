#pragma once

#include "../Materials/Material.h"

// Store values of where ray hit Hittable object
struct HitRecord
{
	// point of intersection
	Point3d point;

	// normal vector to the surface at given point
	Vec normalVec;

	// parameter
	double t;

	// information if ray is inside of outside of the shape
	// isFrontFace will be true if ray is outside of e.g. sphere
	bool isFrontFace;

	// store here material of Hittable object the Ray hit
	std::shared_ptr<Material> material;

	void setFaceNormal(const Ray& ray, const Vec& outwardNormal)
	{
		// Sets the hit record normal vector.
		// The parameter `outwardNormal` is assumed to have unit length.

		isFrontFace = dot_product(ray.getDirection(), outwardNormal) < 0;
		normalVec = isFrontFace ? outwardNormal : -outwardNormal;
	}
};