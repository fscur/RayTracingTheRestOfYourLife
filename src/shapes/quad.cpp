#include "quad.h"

bool xy_quad::hit(const ray& r, float tMin, float tMax, intersection& hit) const
{
    float t = (_z - r.origin.z) / r.direction.z;

    if (t < tMin || t > tMax)
        return false;

    float x = r.origin.x + t*r.direction.x;
    float y = r.origin.y + t*r.direction.y;

    if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
        return false;

    hit.uv = vec2((x - _x0) / (_x1 - _x0), (y - _y0) / (_y1 - _y0));
    hit.t = t;
    hit.material = _material;
    hit.point = r.pointAtParameter(t);
    hit.normal = vec3(0.0f, 0.0f, 1.0f);

    return true;
}

bool yz_quad::hit(const ray& r, float tMin, float tMax, intersection& hit) const
{
    float t = (_x - r.origin.x) / r.direction.x;

    if (t < tMin || t > tMax)
        return false;

    float y = r.origin.y + t*r.direction.y;
    float z = r.origin.z + t*r.direction.z;

    if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
        return false;

    hit.uv = vec2((y - _y0) / (_y1 - _y0), (z - _z0) / (_z1 - _z0));
    hit.t = t;
    hit.material = _material;
    hit.point = r.pointAtParameter(t);
    hit.normal = vec3(1.0f, 0.0f, 0.0f);

    return true;
}

bool zx_quad::hit(const ray& r, float tMin, float tMax, intersection& hit) const
{
    float t = (_y - r.origin.y) / r.direction.y;

    if (t < tMin || t > tMax)
        return false;

    float z = r.origin.z + t*r.direction.z;
    float x = r.origin.x + t*r.direction.x;

    if (z < _z0 || z > _z1 || x < _x0 || x > _x1)
        return false;

    hit.uv = vec2((z - _z0) / (_z1 - _z0), (x - _x0) / (_x1 - _x0));
    hit.t = t;
    hit.material = _material;
    hit.point = r.pointAtParameter(t);
    hit.normal = vec3(0.0f, 1.0f, 0.0f);

    return true;
}