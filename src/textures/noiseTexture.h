#pragma once
#include "texture.h"
#include "../math/perlin.h"

class noiseTexture :
    public texture
{
public:
    noiseTexture(vec3 scale);

    virtual vec3 fetch(const vec2& uv, const vec3 point) const override;

private:
    vec3 _scale;
    perlin _perlin;
};