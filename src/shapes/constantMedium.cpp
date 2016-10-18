#include "constantMedium.h"

inline constantMedium::constantMedium(shape* boundary, float density, texture* texture) :
    _boundary(boundary),
    _phaseFunction(new isotropic(texture)),
    _density(density)
{
}

bool constantMedium::hit(const ray& r, float t_min, float t_max, intersection& hit) const
{
    intersection hit1, hit2;

    if (_boundary->hit(r, MIN_FLOAT, MAX_FLOAT, hit1))
    {
        if (_boundary->hit(r, hit1.t + 0.0001f, MAX_FLOAT, hit2))
        {
            if (hit1.t < t_min)
                hit1.t = t_min;

            if (hit2.t > t_max)
                hit2.t = t_max;

            if (hit1.t >= hit2.t)
                return false;

            if (hit1.t < 0.0f)
                hit1.t = 0.0f;

            float distanceInsideBoundary = (hit2.t - hit1.t) * length(r.direction);
            float hitDistance = -(1.0f / _density) * glm::log(random::next());

            if (hitDistance < distanceInsideBoundary)
            {
                hit.t = hit1.t + hitDistance / length(r.direction);
                hit.point = r.pointAtParameter(hit.t);
                hit.normal = vec3(1.0f, 0.0f, 0.0f);
                hit.material = _phaseFunction;
                hit.uv = hit.uv;
                return true;
            }
        }
    }
    return false;
}

bool constantMedium::createBoundingBox(float t0, float t1, aabb & a) const
{
    return _boundary->createBoundingBox(t0, t1, a);
}

float constantMedium::pdfValue(const vec3 & o, const vec3 & v) const
{
    return _boundary->pdfValue(o, v);
}

vec3 constantMedium::random(const vec3 & o) const
{
    return _boundary->random(o);
}
