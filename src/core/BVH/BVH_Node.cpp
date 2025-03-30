#include "BVH_Node.h"

#include <algorithm>

// BVH_Tree
BVH_Tree::BVH_Tree(HittableObjVec& objects)
{
	m_root = buildBVHTree(objects, 0, objects.size());
}

std::shared_ptr<BVH_Node> BVH_Tree::buildBVHTree(HittableObjVec& objects, size_t start, size_t end)
{
	std::shared_ptr<BVH_Node> root = std::make_shared<BVH_Node>();

	const size_t span = end - start;
	if(span == 1)
	{
		root->m_left = objects[start];
		root->m_right = objects[start];
	}
	else if(span == 2)
	{
		// We assign Hittables, which could be e.g. Spheres as leaves in out BVH structure
		root->m_left = objects[start];
		root->m_right = objects[start+1];
	}
	else
	{
		// If there are more objects, create another BVH containers (BVH_Node)
		const int axis = randomInt(0, 2);
		auto comparator =
			[axis](const std::shared_ptr<HittableObject>& one, const std::shared_ptr<HittableObject> two) -> bool
			{
				const Interval oneInterval = one->getBoundingBox()->getIntervalFromAxis(axis);
				const Interval twoInterval = two->getBoundingBox()->getIntervalFromAxis(axis);
				return oneInterval.m_min < twoInterval.m_min;
			};

		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		size_t mid = start + span / 2;
		root->m_left = buildBVHTree(objects, start, mid);
		root->m_right = buildBVHTree(objects, mid, end);
	}

	root->setBoundingBox(
		std::make_shared<BoundingBox>(root->m_left->getBoundingBox(), root->m_right->getBoundingBox())
	);

	return root;
}

bool BVH_Tree::hit(const Ray& ray, Interval t_MinMax, HitRecord& hitRecord) const
{
	if(m_root)
		return m_root->hit(ray, t_MinMax, hitRecord);

	return false;
}

// BVH_Node
bool BVH_Node::hit(const Ray& ray, Interval ray_t, HitRecord& hitRecord) const
{
	if (!getBoundingBox()->hit(ray, ray_t))
		return false;

	const bool hitLeft = m_left && m_left->hit(ray, ray_t, hitRecord);
	if (hitLeft)
		ray_t.m_max = hitRecord.t;

	const bool hitRight = m_right && m_right->hit(ray, ray_t, hitRecord);

	return hitLeft || hitRight;
}