#include "onb.h"

onb::onb() :
    u(vec3(1.0f, 0.0f, 0.0f)),
    v(vec3(0.0f, 1.0f, 0.0f)),
    w(vec3(0.0f, 0.0f, 1.0f))
{
}

onb::onb(vec3 direction)
{
    w = normalize(direction);
    vec3 a = fabs(w.x) > 0.9f ? vec3(0.0f, 1.0f, 0.0f) : vec3(1.0f, 0.0f, 0.0f);
    v = normalize(cross(w, a));
    u = cross(w, v);
}

vec3 onb::transform(const vec3 & a) const { return a.x*u + a.y*v + a.z*w; }
