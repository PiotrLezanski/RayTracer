#include "BVH_Node.h"

BVH_Node::BVH_Node(const HittableScene& scene)
{
    HittableVec objects = scene.getScene();
	createTree(objects, 0, objects.size());
}

void BVH_Node::createTree(HittableVec& objects, size_t start, size_t end)
{
    const int axis = randomInt(0, 2);
    const size_t object_span = end - start;

    auto comparator =
        [axis](const std::shared_ptr<Hittable>& one, const std::shared_ptr<Hittable> two) -> bool
        {
            const Interval oneInterval = one->getBoundingBox()->getIntervalFromAxis(axis);
            const Interval twoInterval = two->getBoundingBox()->getIntervalFromAxis(axis);
            return oneInterval.m_min < twoInterval.m_min;
        };

    if (object_span == 1) 
    {
        m_left = objects[start];
        m_right = objects[start];
    }
    else if (object_span == 2) 
    {
        m_left = objects[start];
        m_right = objects[start+1];
    }
    else
    {
        auto left = std::make_shared<BVH_Node>();
        auto right = std::make_shared<BVH_Node>();

        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        const size_t mid = start + object_span / 2;

        left->createTree(objects, start, mid);
        right->createTree(objects, mid, end);

        m_left = left;
        m_right = right;
    }

    m_bbox = std::make_shared<BoundingBox>(m_left->getBoundingBox(), m_right->getBoundingBox());
}

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

void BVH_Node::setLeft(std::shared_ptr<Hittable> left)
{
	m_left = left;
}

void BVH_Node::setRight(std::shared_ptr<Hittable> right)
{
	m_right = right;
}
