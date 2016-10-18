#include "cosinePdf.h"

cosinePdf::cosinePdf(const vec3 & direction) :
    _uvw(direction)
{
}

float cosinePdf::value(const vec3 & direction) const
{
    float cosine = dot(normalize(direction), _uvw.w);

    if (cosine > 0.0f)
        return cosine * π¯¹;
    else
        return 0.0f;
}

vec3 cosinePdf::generate() const
{
    return _uvw.transform(sampler::randomCosineDirection());
}
