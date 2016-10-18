#include "noiseTexture.h"

noiseTexture::noiseTexture(vec3 scale) :
    _scale(scale)
{}

vec3 noiseTexture::fetch(const vec2 & uv, const vec3 point) const
{
    return vec3(1.0f) * _perlin.noise(_scale * point);
}
