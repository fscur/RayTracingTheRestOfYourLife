#include "box.h"

box::box() {}

box::box(const vec3 & p0, const vec3 & p1, material * material)
{
    _pMin = p0;
    _pMax = p1;

    _shapeList.add(new xy_quad(rectangle<float>(p0.x, p0.y, p1.x - p0.x, p1.y - p0.y), p1.z, material));
    _shapeList.add(new flipNormals(new xy_quad(rectangle<float>(p0.x, p0.y, p1.x - p0.x, p1.y - p0.y), p0.z, material)));
    _shapeList.add(new zx_quad(rectangle<float>(p0.z, p0.x, p1.z - p0.z, p1.x - p0.x), p1.y, material));
    _shapeList.add(new flipNormals(new zx_quad(rectangle<float>(p0.z, p0.x, p1.z - p0.z, p1.x - p0.x), p0.y, material)));
    _shapeList.add(new yz_quad(rectangle<float>(p0.y, p0.z, p1.y - p0.y, p1.z - p0.z), p1.x, material));
    _shapeList.add(new flipNormals(new yz_quad(rectangle<float>(p0.y, p0.z, p1.y - p0.y, p1.z - p0.z), p0.x, material)));
}

bool box::hit(const ray& r, float tMin, float tMax, intersection& hit) const
{
    return _shapeList.hit(r, tMin, tMax, hit);
}

bool box::createBoundingBox(float t0, float t1, aabb & box) const
{
    box = aabb(_pMin, _pMax);
    return true;
}
