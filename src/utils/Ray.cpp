#include "Ray.h"
#include "../Scene/Shapes/Sphere.h"

Color Ray::calculateColor(const Hittable& scene) const
{
	HitRecord hitRecord;
	if(scene.hit(*this, Interval(0, INF), hitRecord))
		return 0.5 * (hitRecord.normalVec + Color(1, 1, 1));

	const Vec unitDirection = unit_vector(getDirection());
	double a = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}