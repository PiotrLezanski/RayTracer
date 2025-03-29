#pragma once

#include "HitRecord.h"
#include "../../utils/Ray.h"
#include "../../utils/Interval.h"

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& ray, Interval t_MinMax, HitRecord& hitRecord) const = 0;
};