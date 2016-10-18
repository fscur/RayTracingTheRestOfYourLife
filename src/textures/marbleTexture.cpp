#include "marbleTexture.h"

marbleTexture::marbleTexture(vec3 scale, vec3 color) :
    _scale(scale),
    _color(color)
{}

vec3 marbleTexture::fetch(const vec2 & uv, const vec3 point) const
{
    return _color * 0.5f * (1.0f + sin(_scale.x*point.x + 5.0f * perlin::turbulence(_scale.x * point)));
}
