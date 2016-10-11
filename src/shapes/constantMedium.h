#pragma once
#include <iostream>
#include "../common/random.h"
#include "../materials/isotropic.h"
#include "../textures/texture.h"

#include "shape.h"


class constantMedium : 
    public shape {
public:
    constantMedium(shape* boundary, float density, texture* texture) : 
        _boundary(boundary), 
        _density(density) 
    { 
        _phaseFunction = new isotropic(texture); 
    }
    
    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;
    
    virtual bool createBoundingBox(float t0, float t1, aabb& a) const 
    {
        return _boundary->createBoundingBox(t0, t1, a);
    }

private:
    shape* _boundary;
    float _density;
    material* _phaseFunction;
};

bool constantMedium::hit(const ray& r, float t_min, float t_max, intersection& hit) const 
{
    intersection hit1, hit2;

    auto maxFloat = std::numeric_limits<float>().max();
    auto minFloat = std::numeric_limits<float>().lowest();

    if (_boundary->hit(r, minFloat, maxFloat, hit1)) 
    {
        if (_boundary->hit(r, hit1.t + 0.0001, maxFloat, hit2)) 
        {
            if (hit1.t < t_min)
                hit1.t = t_min;

            if (hit2.t > t_max)
                hit2.t = t_max;

            if (hit1.t >= hit2.t)
                return false;

            if (hit1.t < 0)
                hit1.t = 0;

            float distanceInsideBoundary = (hit2.t - hit1.t) * length(r.direction);
            float hitDistance = -(1.0f/_density) * glm::log(random::next());

            if (hitDistance < distanceInsideBoundary) 
            {
                hit.t = hit1.t + hitDistance / length(r.direction);
                hit.point = r.pointAtParameter(hit.t);
                hit.normal = vec3(1, 0, 0);  // arbitrary
                hit.material = _phaseFunction;
                hit.uv = hit.uv;
                return true;
            }
        }
    }
    return false;
}
