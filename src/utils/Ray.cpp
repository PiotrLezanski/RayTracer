#include "Ray.h"
#include "../Scene/Shapes/Sphere.h"
#include "../Scene/Materials/Material.h"

Color Ray::calculateColor(const Hittable& scene, int depth) const
{
	if (depth <= 0)
		return DEFAULT_COLOR;

	HitRecord hitRecord;
	if (scene.hit(*this, Interval(0.001, INF), hitRecord))
	{
		Ray scattered;
		Color attenuation;
		if (hitRecord.material->scatter(*this, hitRecord, attenuation, scattered))
			return attenuation * scattered.calculateColor(scene, depth - 1);
		return DEFAULT_COLOR;
	}

	const Vec unitDirection = unit_vector(getDirection());
	double a = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}