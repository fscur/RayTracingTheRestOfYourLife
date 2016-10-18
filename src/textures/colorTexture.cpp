#include "colorTexture.h"

colorTexture* colorTexture::red = new colorTexture(vec3(0.97f, 0.0f, 0.0f));
colorTexture* colorTexture::green = new colorTexture(vec3(0.0f, 0.97f, 0.0f));
colorTexture* colorTexture::blue = new colorTexture(vec3(0.0f, 0.0f, 0.97f));
colorTexture* colorTexture::black = new colorTexture(vec3(0.03f, 0.03f, 0.03f));
colorTexture* colorTexture::white = new colorTexture(vec3(0.97f, 0.97f, 0.97f));

colorTexture::colorTexture(const vec3 & color) :
    _color(color)
{
}

vec3 colorTexture::fetch(const vec2 & uv, const vec3 point) const
{
    return _color;
}
