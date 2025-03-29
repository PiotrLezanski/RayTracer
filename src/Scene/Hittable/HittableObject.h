#pragma once

#include "Hittable.h"
#include "../../core/BVH/BoundingBox.h"

class Material;

// Interface for objects that Ray can intersect with e.g. Sphere, BVH_Node
// Every Hittable object has it's own bounding box
class HittableObject : public Hittable
{
public:
	// Default contructor needed for HittableScene, which does not need it's own material
	HittableObject() = default;
	HittableObject(std::shared_ptr<Material> material) : m_material(material) {}
	
	// return copy of the material
	std::shared_ptr<Material> getMaterial() const { return m_material; }
	void setMaterial(const std::shared_ptr<Material>& newMaterial) { m_material = newMaterial; }
	
	auto getBoundingBox() const { return m_bbox; }
	void setBoundingBox(const std::shared_ptr<BoundingBox>& bbox) { m_bbox = bbox; }

protected:
	// Material of the Hittable object e.g. Sphere
	std::shared_ptr<Material> m_material;

	std::shared_ptr<BoundingBox> m_bbox = std::make_shared<BoundingBox>();
};