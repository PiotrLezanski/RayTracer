#pragma once

#include "Material.h"

class Refractive : public Material
{
public:
    Refractive(double refractionIndex) : m_refractionIndex(refractionIndex) {}

    bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const override;

private:
    // Determines how light bends (refracts) when entering or exiting the material.
    // E.g. for vacuum is is exacly 1.0, as there is no bend at all.
    // Air ~1.0003, because there is slight bend, but not visible with eye.
    // Water ~1.333, when putting e.g. pen into the water we can see it's structure bends.
    double m_refractionIndex;
};

bool Refractive::scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double ri = hitRecord.isFrontFace ? (1.0 / m_refractionIndex) : m_refractionIndex;

    Vec unitDirection = unit_vector(rayIn.getDirection());
    Vec refracted = refract(unitDirection, hitRecord.normalVec, ri);

	const double cosTheta = std::fmin(dot_product(-unitDirection, hitRecord.normalVec), 1.0);
    const double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    const bool canRefract = ri * sinTheta <= 1.0;
    Vec direction;
    if (canRefract && reflectance(cosTheta, ri) <= 1)
        direction = refract(unitDirection, hitRecord.normalVec, ri);
    else
        direction = reflect(unitDirection, hitRecord.normalVec);

    rayScattered = Ray(hitRecord.point, direction);
    return true;
}