#include "Ray.h"


Color Ray::calculateColor() const
{
	Vec unitDirection = unit_vector(getDirection());
	double a = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}