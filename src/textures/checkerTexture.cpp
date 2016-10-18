#include "checkerTexture.h"

checkerTexture::checkerTexture(texture * odd, texture * even) :
    _odd(odd),
    _even(even)
{}

vec3 checkerTexture::fetch(const vec2 & uv, const vec3 point) const
{
    float sines = sin(10 * point.x) * sin(10 * point.y) * sin(10 * point.z);
    return sines < 0 ? _odd->fetch(uv, point) : _even->fetch(uv, point);
}
