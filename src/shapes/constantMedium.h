#pragma once

#include "../common/random.h"
#include "../materials/isotropic.h"
#include "../textures/texture.h"
#include "shape.h"

class constantMedium : 
    public shape {
public:
    constantMedium(shape* boundary, float density, texture* texture);
    
    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const override;
    virtual bool createBoundingBox(float t0, float t1, aabb& a) const override;
    virtual float pdfValue(const vec3& o, const vec3& v) const override;
    virtual vec3 random(const vec3& o) const override;

private:
    shape* _boundary;
    material* _phaseFunction;
    float _density;
};
