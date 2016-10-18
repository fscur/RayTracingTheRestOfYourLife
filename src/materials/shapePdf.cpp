#include "shapePdf.h"

shapePdf::shapePdf(shape* shape, const vec3& origin) :
    _shape(shape), _origin(origin)
{}

float shapePdf::value(const vec3& direction) const
{
    return _shape->pdfValue(_origin, direction);
}

vec3 shapePdf::generate() const
{
    return _shape->random(_origin);
}
