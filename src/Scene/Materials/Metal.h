#pragma once

#include "Material.h"

// Metal just reflects rays
class Metal : public Material
{
public:
    Metal(const Color& albedo, double fuzz) : m_albedo(albedo), m_fuzz(std::clamp(fuzz, 0.0, 1.0)) {}

    bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const override;

private:
    // `albedo` property defines how much light the material reflects.
    // E.g. a white surface has a high albedo (reflects most light),
    // while a black surface has a low albedo (absorbs most light)
    Color m_albedo;

    // Fuzz controls the roughness of the surface for reflective materials.
    // A value of 0.0 represents a perfectly smooth surface (ideal mirror),
	// while higher values create a rougher appearance
    double m_fuzz;
};

bool Metal::scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const
{
	Vec reflected = reflect(rayIn.getDirection(), hitRecord.normalVec);

    // apply fuzz
    if(m_fuzz > 0)
        reflected = unit_vector(reflected) + (m_fuzz * randomUnitVec());

    rayScattered = Ray(hitRecord.point, reflected);
    attenuation = m_albedo;
    return dot_product(rayScattered.getDirection(), hitRecord.normalVec) > 0;
}