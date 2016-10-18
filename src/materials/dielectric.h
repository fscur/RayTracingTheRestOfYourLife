#pragma once

#include "material.h"

class dielectric :
    public material
{
public:
    dielectric(float refractionIndex);
    bool scatter(const ray& r, const intersection& hit, scatterRecord& srec) const;

private:
    float _indexOfRefraction;
};


