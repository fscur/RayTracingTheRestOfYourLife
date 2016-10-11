#pragma once
#include "../common/types.h"
#include "ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

#undef min
#undef max

struct aabb
{
    aabb() {}

    aabb(const vec3& min, const vec3& max) :
        min(min),
        max(max)
    {
    }

    static aabb getSurroundingAabb(const aabb& a, const aabb& b)
    {
        vec3 min(
            ffmin(a.min.x, b.min.x),
            ffmin(a.min.y, b.min.y),
            ffmin(a.min.z, b.min.z));

        vec3 max(
            ffmax(a.max.x, b.max.x),
            ffmax(a.max.y, b.max.y),
            ffmax(a.max.z, b.max.z));

        return aabb(min, max);
    }

    bool intersect(const ray& r, float tMin, float tMax) const
    {
        for (byte i = 0; i < 3; ++i)
        {
            float m0 = (min[i] - r.origin[i]) * r.invDir[i];
            float m1 = (max[i] - r.origin[i]) * r.invDir[i];

            if (r.invDir[i] < 0.0f)
                std::swap(m0, m1);

            tMin = m0 > tMin ? m0 : tMin;
            tMax = m1 < tMax ? m1 : tMax;

            if (tMax <= tMin)
                return false;
        }

        return true;
    }

public:
    vec3 min;
    vec3 max;
};
