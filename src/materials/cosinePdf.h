#pragma once
#include "pdf.h"

class cosinePdf :
    public pdf
{
public:
    cosinePdf(const vec3& w);
    virtual float value(const vec3& direction) const override;
    virtual vec3 generate() const override;

private:
    onb _uvw;
};