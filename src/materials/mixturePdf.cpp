#include "mixturePdf.h"

mixturePdf::mixturePdf(pdf * pdf0, pdf * pdf1)
{
    _pdfs[0] = pdf0;
    _pdfs[1] = pdf1;
}

float mixturePdf::value(const vec3 & direction) const
{
    return 0.5f * _pdfs[0]->value(direction) + 0.5f * _pdfs[1]->value(direction);
}

vec3 mixturePdf::generate() const
{
    if (random::next() < 0.5f)
        return _pdfs[0]->generate();
    else
        return _pdfs[1]->generate();
}
