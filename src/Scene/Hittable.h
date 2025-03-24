#pragma once

#include "../utils/Ray.h"
#include "../utils/Interval.h"
#include "../core/BVH/BoundingBox.h"

class Material;

// Store values of where ray hit Hittable object
struct HitRecord
{
	// point of intersection
	Point3d point;

	// normal vector to the surface at given point
	Vec normalVec;

	// parameter
	double t;

	// information if ray is inside of outside of the shape
	// isFrontFace will be true if ray is outside of e.g. sphere
	bool isFrontFace;

	// store here material of Hittable object the Ray hit
	std::shared_ptr<Material> material;

	void setFaceNormal(const Ray& ray, const Vec& outwardNormal)
	{
		// Sets the hit record normal vector.
		// The parameter `outwardNormal` is assumed to have unit length.

		isFrontFace = dot_product(ray.getDirection(), outwardNormal) < 0;
		normalVec = isFrontFace ? outwardNormal : -outwardNormal;
	}
};

// Interface for objects that Ray can intersect with e.g. Sphere, BVH_Node
// Every Hittable object has it's own bounding box
class Hittable
{
public:
	// Default contructor needed for HittableScene, which does not need it's own material
	Hittable() = default;
	Hittable(std::shared_ptr<Material> material) : m_material(material) {}

	virtual ~Hittable() = default;

	virtual bool hit(const Ray& ray, Interval t_MinMax, HitRecord& hitRecord) const = 0;
	
	// return copy of the material
	std::shared_ptr<Material> getMaterial() const { return m_material; }
	void setMaterial(const std::shared_ptr<Material>& newMaterial) { m_material = newMaterial; }
	
	auto getBoundingBox() const { return m_bbox; }

protected:
	// Material of the Hittable object e.g. Sphere
	std::shared_ptr<Material> m_material;

	std::shared_ptr<BoundingBox> m_bbox;
};