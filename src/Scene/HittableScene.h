#pragma once

#include "Hittable.h"

using HittableVec = std::vector<std::shared_ptr<Hittable>>;

class HittableScene : public Hittable
{
public:
	HittableScene() = default;
	explicit HittableScene(std::shared_ptr<Hittable> obj);

	void add(const std::shared_ptr<Hittable> obj);
	const HittableVec& getScene() const { return m_sceneVec; };

	// Hit all objects in the m_sceneVec.
	// Return true if anything was hit.
	bool hit(const Ray& ray, Interval t_MinMax, HitRecord& hitRecord) const override;

	size_t size() const { return m_sceneVec.size(); }

private:
	// vector of Shapes
	HittableVec m_sceneVec;
};