#pragma once

#include "Material.h"

// This class represents a diffuse material using the Lambertian reflection model.
// This type of material scatters incoming light uniformly in all directions, 
// creating a matte (non-shiny) appearance. Examples of Lambertian surfaces are
// chalk, paper, or unpolished wood. 

// The class takes in a color which determines the material's appearance under light. 
// When a ray hits the material, it is scattered in a random direction, 
// and the scattered ray carries a portion of this color.
class Lambertian : public Material
{
public:
    Lambertian(const Color& albedo) : m_albedo(albedo) {}

    bool scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const override;

private:
    // `albedo` property defines how much light the material reflects.
    // E.g. a white surface has a high albedo (reflects most light),
    // while a black surface has a low albedo (absorbs most light)
    Color m_albedo;
};

bool Lambertian::scatter(const Ray& rayIn, const HitRecord& hitRecord, Color& attenuation, Ray& rayScattered) const
{
    // Scatter direction is a random unit vector around the hit normal
    Color scatterDirection = hitRecord.normalVec + randomUnitVec();
    if (scatterDirection.isCloseToZero())
        scatterDirection = hitRecord.normalVec;

    // Create a new scattered ray starting from the hit point
    rayScattered = Ray(hitRecord.point, scatterDirection);

    // Attenuation is set to the material's albedo (reflectivity)
    attenuation = m_albedo;
    return true;
}