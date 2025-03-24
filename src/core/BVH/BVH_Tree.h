#pragma once

#include "../../Scene/Hittable.h"

class BVH_Node;

class BVH_Tree
{
public:
	BVH_Tree(std::unique_ptr<BVH_Node> root);

	BVH_Tree(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end);

private:
	std::unique_ptr<BVH_Node> m_root;
};

class BVH_Node : public Hittable
{
public:
	bool hit(const Ray& ray, Interval ray_t, HitRecord& hitRecord) const override;

	const Hittable* getLeft() const { return m_left.get(); }
	void setLeft(std::unique_ptr<Hittable> left);

	const Hittable* getRight() const { return m_right.get(); }
	void setRight(std::unique_ptr<Hittable> right);

private:
	std::unique_ptr<Hittable> m_left;
	std::unique_ptr<Hittable> m_right;
};