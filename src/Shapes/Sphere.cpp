#include "Sphere.h"

Sphere::Sphere(Point3d center, double radius)
	: m_center(center), m_radius(radius)
{
}

bool Sphere::isHittableBy(const Ray& ray)
{
    const Vec oc = getCenter() - ray.getOrigin();
    auto a = dot_product(ray.getDirection(), ray.getDirection());
    auto b = -2.0 * dot_product(ray.getDirection(), oc);
    auto c = dot_product(oc, oc) - getRadius() * getRadius();
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}