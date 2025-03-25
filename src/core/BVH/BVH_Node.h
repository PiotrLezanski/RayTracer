#pragma once

#include "../../Scene/Hittable.h"
#include "../../Scene/HittableScene.h"

#include <algorithm>

class BVH_Node : public Hittable
{
public:
	BVH_Node() = default;
	BVH_Node(const HittableScene& scene);

public:
	void createTree(HittableVec& objects, size_t start, size_t end);

public:
	bool hit(const Ray& ray, Interval ray_t, HitRecord& hitRecord) const override;

	const Hittable* getLeft() const { return m_left.get(); }
	void setLeft(std::shared_ptr<Hittable> left);

	const Hittable* getRight() const { return m_right.get(); }
	void setRight(std::shared_ptr<Hittable> right);

private:
	std::shared_ptr<Hittable> m_left;
	std::shared_ptr<Hittable> m_right;
};