#pragma once
#include "material.h"
#include "../textures/texture.h"
#include "../samplers/sampler.h"

class isotropic : 
    public material 
{
public:
    isotropic(texture* albedo);

    virtual bool scatter(const ray& r, const intersection& hit, scatterRecord& srec) const override;

private:
    texture* _albedo;
};
