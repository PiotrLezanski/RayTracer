#pragma once

#include "../../Scene/Hittable/HittableScene.h"

class BVH_Node;

class BVH_Tree : public HittableObject
{
public:
	BVH_Tree(HittableObjVec& objects);

	std::shared_ptr<BVH_Node> buildBVHTree(HittableObjVec& objects, size_t start, size_t end);

	bool hit(const Ray& ray, Interval t_MinMax, HitRecord& hitRecord) const;

private:
	std::shared_ptr<BVH_Node> m_root;
};

// Behaves like container, storing another containers or
// specific Hittable objects e.g. Spheres 
class BVH_Node : public HittableObject
{
public:
	BVH_Node() = default;

public:
	bool hit(const Ray& ray, Interval ray_t, HitRecord& hitRecord) const override;

	std::shared_ptr<HittableObject> m_left;
	std::shared_ptr<HittableObject> m_right;
};