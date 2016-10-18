#pragma once
#include "pdf.h"

class shapePdf :
    public pdf {
public:
    shapePdf(shape* shape, const vec3& origin);

    virtual float value(const vec3& direction) const override;
    virtual vec3 generate() const override;

private:
    vec3 _origin;
    shape* _shape;
};
