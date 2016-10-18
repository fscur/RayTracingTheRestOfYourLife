#pragma once
#include "shape.h"

class rotateY : 
    public shape
{
public:
    rotateY(shape* shape, float angle);
    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const override;
    virtual bool createBoundingBox(float t0, float t1, aabb& a) const override;

private:
    shape* _shape;
    float _sinTheta;
    float _cosTheta;
    bool _hasBox;
    aabb _aabb;
};
