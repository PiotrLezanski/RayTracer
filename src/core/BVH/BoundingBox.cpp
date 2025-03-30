#include "BoundingBox.h"

BoundingBox::BoundingBox()
	: BoundingBox(EMPTY_INTERVAL, EMPTY_INTERVAL, EMPTY_INTERVAL)
{}

BoundingBox::BoundingBox(const Interval& x, const Interval& y, const Interval& z)
	: m_x(x), m_y(y), m_z(z)
{}

BoundingBox::BoundingBox(const Point3d& p1, const Point3d& p2)
{
	m_x = p1.x() < p2.x() ? Interval(p1.x(), p2.x()) : Interval(p2.x(), p1.x());
	m_y = p1.y() < p2.y() ? Interval(p1.y(), p2.y()) : Interval(p2.y(), p1.y());
	m_z = p1.z() < p2.z() ? Interval(p1.z(), p2.z()) : Interval(p2.z(), p1.z());
}

BoundingBox::BoundingBox(std::shared_ptr<BoundingBox> a, std::shared_ptr<BoundingBox> b)
{
	m_x = Interval(a->m_x, b->m_x);
	m_y = Interval(a->m_y, b->m_y);
	m_z = Interval(a->m_z, b->m_z);	
}

const Interval& BoundingBox::getIntervalFromAxis(int axis) const
{
	if (axis == 0) return m_x;
	if (axis == 1) return m_y;
	return m_z;
}

bool BoundingBox::hit(const Ray& r, Interval ray_t)
{
	const Point3d& rayOrigin = r.getOrigin();
	const Vec& rayDirection = r.getDirection();

	for(int axis=0; axis<3; ++axis)
	{
		const Interval& axisInterval = getIntervalFromAxis(axis);
		const double dirInv = 1.0 / rayDirection[axis]; // to omit division later

		double t_min = (axisInterval.m_min - rayOrigin[axis]) * dirInv;
		double t_max = (axisInterval.m_max - rayOrigin[axis]) * dirInv;

		if (t_min > t_max) std::swap(t_min, t_max);

		// Update min and max to tighten intersection interval
		if (t_min > ray_t.m_min) ray_t.m_min = t_min;
		if (t_max < ray_t.m_max) ray_t.m_max = t_max;

		// Check if intersection interval is not empty
		if (ray_t.size() <= 0)
			return false;
	}
	return true;
}

int BoundingBox::getLongestAxis() const
{
	const double sizeX = m_x.size();
	const double sizeY = m_y.size();
	const double sizeZ = m_z.size();

	if (sizeX > sizeY && sizeX > sizeZ)
		return 0;
	if (sizeY > sizeZ)
		return 1;
	else
		return 2;
}
