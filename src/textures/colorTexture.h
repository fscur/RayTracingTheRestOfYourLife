#pragma once
#include "texture.h"

class colorTexture :
    public texture
{
public:
    static colorTexture* red;
    static colorTexture* green;
    static colorTexture* blue;
    static colorTexture* black;
    static colorTexture* white;
    

public:
    colorTexture(const vec3& color);
    virtual vec3 fetch(const vec2& uv, const vec3 point) const override;

private:
    vec3 _color;
};