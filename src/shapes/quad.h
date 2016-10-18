#pragma once

#include "shape.h"
#include "../math/rectangle.h"
#include "../common/random.h"

class xy_quad :
    public shape 
{
public:
    xy_quad() 
    {}

    xy_quad(rectangle<float> rect, float z, material* material) :
        _x0(rect.x), 
        _x1(rect.w + rect.x), 
        _y0(rect.y), 
        _y1(rect.h + rect.y), 
        _z(z), 
        _material(material)
    {
    
    }

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;

    virtual bool createBoundingBox(float t0, float t1, aabb& a) const 
    {
        a = aabb(vec3(_x0, _y0, _z - 0.0001), vec3(_x1, _y1, _z + 0.0001));
        return true;
    }
    
private:
    material* _material;
    float _x0, _x1, _y0, _y1, _z;
};

class yz_quad :
    public shape
{
public:
    yz_quad()
    {}

    yz_quad(rectangle<float> rect, float x, material* material) :
        _y0(rect.x),
        _y1(rect.w + rect.x),
        _z0(rect.y),
        _z1(rect.h + rect.y),
        _x(x),
        _material(material)
    {

    }

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;

    virtual bool createBoundingBox(float t0, float t1, aabb& a) const
    {
        a = aabb(vec3(_x - 0.0001f, _y0, _z0), vec3(_x + 0.0001f, _y1, _z1));
        return true;
    }

private:
    material* _material;
    float _y0, _y1, _z0, _z1, _x;
};

class zx_quad :
    public shape
{
public:
    zx_quad()
    {}

    zx_quad(rectangle<float> rect, float y, material* material) :
        _z0(rect.x),
        _z1(rect.w + rect.x),
        _x0(rect.y),
        _x1(rect.h + rect.y),
        _y(y),
        _material(material)
    {

    }

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;

    virtual bool createBoundingBox(float t0, float t1, aabb& a) const
    {
        a = aabb(vec3(_x0, _y - 0.0001f, _z0), vec3(_x1, _y + 0.0001f, _z1));
        return true;
    }

    virtual float pdfValue(const vec3& o, const vec3& v) const 
    { 
        intersection tempHit;
        if (this->hit(ray(o, v), 0.001, std::numeric_limits<float>().max(), tempHit))
        {
            float area = (_x1 - _x0)*(_z1 - _z0);
            float dist = tempHit.t * tempHit.t * dot(v, v);
            float cosine = fabs(dot(v, tempHit.normal) / glm::length(v));
            return dist / (cosine*area);
        }
        return 0.0f; 
    }

    virtual vec3 random(const vec3& o) const 
    { 
        vec3 p = vec3(
            _x0 + random::next()*(_x1 - _x0),
            _y,
            _z0 + random::next()*(_z1 - _z0));

        return p - o;
    }

private:
    material* _material;
    float _z0, _z1, _x0, _x1, _y;
};
