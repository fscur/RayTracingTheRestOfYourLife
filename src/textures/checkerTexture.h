#pragma once
#include "texture.h"

class checkerTexture :
    public texture
{
public:
    checkerTexture(texture* odd, texture* even);
    virtual vec3 fetch(const vec2& uv, const vec3 point) const override;

private:
    texture* _odd;
    texture* _even;
};
