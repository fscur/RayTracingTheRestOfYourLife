#pragma once
#include "../math/ray.h"
#include "../math/intersection.h"
#include "../math/aabb.h"

class shape
{
public:
    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const = 0;
    virtual bool createBoundingBox(float t0, float t1, aabb& aabb) const = 0;
    virtual float pdfValue(const vec3& o, const vec3& v) const { return 0.0f; }
    virtual vec3 random(const vec3& o) const { return vec3(1.0f, 0.0f, 0.0); }
};