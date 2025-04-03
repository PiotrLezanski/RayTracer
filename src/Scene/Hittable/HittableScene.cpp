#include "HittableScene.h"

HittableScene::HittableScene(std::shared_ptr<HittableObject> obj)
{
	add(obj);
}

void HittableScene::add(const std::shared_ptr<HittableObject> obj)
{
	if (obj)
	{
		m_sceneVec.emplace_back(obj);
		// Make bounding box bigger
		m_bbox = std::make_shared<BoundingBox>(m_bbox, obj->getBoundingBox());
	}
}

bool HittableScene::hit(const Ray& ray, Interval t_MinMax, HitRecord& hitRecord) const
{
	HitRecord tmpRecord;
	bool isSthHit = false;
	double closest_tmax = t_MinMax.m_max;

	// In BVH structure there is just one element in the scene.
	// This element is single BVH_Tree, so we just hit it's root here.
	for (const auto& obj : getScene())
	{
		if (obj->hit(ray, Interval(t_MinMax.m_min, closest_tmax), tmpRecord))
		{
			isSthHit = true;
			closest_tmax = tmpRecord.t;
			hitRecord = tmpRecord;
		}
	}
	return isSthHit;
}
