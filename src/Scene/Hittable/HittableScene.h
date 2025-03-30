#pragma once

#include "HittableObject.h"

using HittableObjVec = std::vector<std::shared_ptr<HittableObject>>;

class HittableScene : public HittableObject
{
public:
	HittableScene() = default;
	HittableScene(std::shared_ptr<HittableObject> obj);

	void add(const std::shared_ptr<HittableObject> obj);

	const HittableObjVec& getScene() const { return m_sceneVec; }
	HittableObjVec& getScene() { return m_sceneVec; }

	// Hit all objects in the m_sceneVec.
	// Return true if anything was hit.
	bool hit(const Ray& ray, Interval t_MinMax, HitRecord& hitRecord) const override;

	size_t size() const { return m_sceneVec.size(); }

private:
	// vector of Shapes
	HittableObjVec m_sceneVec;
};