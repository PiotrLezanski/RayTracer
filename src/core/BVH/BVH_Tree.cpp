#include "BVH_Tree.h"

BVH_Tree::BVH_Tree(std::unique_ptr<BVH_Node> root)
	: m_root(std::move(root))
{}

bool BVH_Node::hit(const Ray& ray, Interval ray_t, HitRecord& hitRecord) const
{
	if (!getBoundingBox()->hit(ray, ray_t))
		return false;

	const bool hitLeft = m_left->hit(ray, ray_t, hitRecord);
	if (hitLeft)
		ray_t.m_max = hitRecord.t;

	const bool hitRight = m_right->hit(ray, ray_t, hitRecord);

	return hitLeft || hitRight;
}

void BVH_Node::setLeft(std::unique_ptr<Hittable> left)
{
	m_left = std::move(left);
}

void BVH_Node::setRight(std::unique_ptr<Hittable> right)
{
	m_right = std::move(right);
}
