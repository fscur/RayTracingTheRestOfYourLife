#pragma once
#include "shape.h"
#include <vector>
#include <iostream>

class shapeList :
    public shape
{
public:
    shapeList() {}

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const override;
    virtual bool createBoundingBox(float t0, float t1, aabb& a) const override;
    virtual float pdfValue(const vec3& o, const vec3& v) const override;
    virtual vec3 random(const vec3& o) const override;
    void add(shape* shape);

private:
    std::vector<shape*> _shapes;
};