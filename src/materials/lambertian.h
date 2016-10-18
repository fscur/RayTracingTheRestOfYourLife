#pragma once
#include "../textures/texture.h"
#include "material.h"

class lambertian :
    public material
{
public:
    lambertian(texture* albedo);

    virtual bool scatter(
        const ray& r, 
        const intersection& hit, 
        scatterRecord& srec) const;

    virtual float scatteringPdf(
        const ray& r, 
        const intersection& hit, 
        const ray& scattered) const;

private:
    texture* _albedo;
};


