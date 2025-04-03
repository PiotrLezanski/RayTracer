#pragma once

#include "HitRecord.h"
#include "../../utils/Ray.h"
#include "../../utils/Interval.h"

// Interface for all objects that technically can be hit
// but do not need their own Material or BBox
class Hittable
{
public:
	virtual ~Hittable() = default;

	// Hit Hittable with given ray.
	// We store interval of valid t-parameter in t_MinMax variable.
	// hitRecord stores useful information about particular hit.
	virtual bool hit(const Ray& ray, Interval t_MinMax, HitRecord& hitRecord) const = 0;
};