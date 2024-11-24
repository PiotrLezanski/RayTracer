#include "Sphere.h"

Sphere::Sphere(Point3d center, double radius)
	: m_center(center), m_radius(radius)
{
}

bool Sphere::hit(const Ray& ray, Interval t_MinMax, HitRecord& rec) const
{
    // simple math to get point of intersection of ray and sphere
    const Vec oc = getCenter() - ray.getOrigin();
    const auto a = ray.getDirection().cords_squared();
    const auto h = dot_product(ray.getDirection(), oc);
    const auto c = oc.cords_squared() - getRadius() * getRadius();
    const auto discriminant = h*h - a*c;

    if (discriminant < 0)
        return false;

    const auto sqrt_d = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range - between ray_tmin and ray_tmax
    auto root = (h - sqrt_d) / a;
    if (!t_MinMax.surrounds(root)) 
    {
        root = (h + sqrt_d) / a;
        if (!t_MinMax.surrounds(root))
            return false;
    }

    rec.point = ray.at(root);
    rec.normalVec = (rec.point - getCenter()) / getRadius();
    rec.t = root;
    Vec outwardNormal = (rec.point - getCenter()) / getRadius();
    rec.setFaceNormal(ray, outwardNormal);

	return true;
}