#pragma once

#include "../Hittable/HittableObject.h"
#include "../../utils/Ray.h"

class Sphere : public HittableObject
{
public:
	Sphere(Point3d center, double radius, std::shared_ptr<Material> material);

	bool hit(const Ray& ray, Interval t_MinMax, HitRecord& rec) const override;

	[[nodiscard]] const Point3d& getCenter() const { return m_center; }
	[[nodiscard]] const double& getRadius() const { return m_radius; }

private:
	Point3d m_center;
	double m_radius;
};