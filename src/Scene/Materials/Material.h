#pragma once

#include "../../utils/Ray.h"
#include "../Hittable.h"

// Base class of all materials in Ray Tracer
class Material
{
public:
	virtual ~Material() = default;

	// This method simulates the scattering of light when it interacts with a material surface.
	// It determines how the incoming ray is altered after hitting a surface.
	// Attenuation says how much light is absorbed or reflected by the material.
	// 'rayScattered' stores ray after scattering of incoming ray.
	virtual bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const = 0;
};