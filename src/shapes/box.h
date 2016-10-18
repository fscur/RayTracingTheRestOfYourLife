#pragma once

#include "shape.h"
#include "shapeList.h"
#include "quad.h"
#include "flipNormals.h"

class box : 
    public shape {
public:
    box();
    box(const vec3& p0, const vec3& p1, material* material);
    
    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;
    virtual bool createBoundingBox(float t0, float t1, aabb& box) const;

private:
    vec3 _pMin;
    vec3 _pMax;
    shapeList _shapeList;
};