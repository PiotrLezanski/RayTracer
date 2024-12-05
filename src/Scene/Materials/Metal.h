#pragma once

#include "Material.h"

// Metal just reflects rays
class Metal : public Material
{
public:
    Metal(const Color& albedo) : m_albedo(albedo) {}

    bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const override;

private:
    // `albedo` property defines how much light the material reflects.
    // E.g. a white surface has a high albedo (reflects most light),
    // while a black surface has a low albedo (absorbs most light)
    Color m_albedo;
};

bool Metal::scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const
{
    const Vec reflected = reflect(rayIn.getDirection(), hitRecord.normalVec);
    rayScattered = Ray(hitRecord.point, reflected);
    attenuation = m_albedo;
    return true;
}