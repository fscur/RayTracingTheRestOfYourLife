#include "../samplers/sampler.h"

#include "emissive.h"

emissive::emissive(texture* albedo) :
    _albedo(albedo)
{
}

bool emissive::scatter(const ray& r, const intersection& hit, scatterRecord& srec) const
{
    return false;
}

vec3 emissive::emitted(const ray& r, const intersection& hit, const vec2& uv, const vec3& point) const
{
    if (dot(hit.normal, r.direction) < 0.0f)
        return _albedo->fetch(uv, point);
    else
        return vec3(1.0f);
}
