#include "HittableScene.h"

void HittableScene::add(const std::shared_ptr<Hittable> obj)
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
