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
    // Air ~1.0003, because there is slight bend, but not visible with eye
    // Water ~1.333, when putting e.g. pen into the water we can see it's structure bends.
    double m_refractionIndex;
};

bool Refractive::scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double ri = hitRecord.isFrontFace ? (1.0 / m_refractionIndex) : m_refractionIndex;

    Vec unit_direction = unit_vector(rayIn.getDirection());
    Vec refracted = refract(unit_direction, hitRecord.normalVec, ri);

    rayScattered = Ray(hitRecord.point, refracted);
    return true;
}