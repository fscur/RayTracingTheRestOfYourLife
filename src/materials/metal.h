#pragma once
#include "../textures/texture.h"
#include "material.h"

class metal :
    public material
{
public:
    metal(texture* albedo, float roughness);
    bool scatter(const ray& r, const intersection& hit, scatterRecord& srec) const;

private:
    texture* _albedo;
    float _roughness;
};


