#pragma once
#include "texture.h"
#include "../math/perlin.h"

class marbleTexture :
    public texture
{
public:
    marbleTexture(vec3 scale, vec3 color);
    virtual vec3 fetch(const vec2& uv, const vec3 point) const override;

private:
    vec3 _scale;
    vec3 _color;
};