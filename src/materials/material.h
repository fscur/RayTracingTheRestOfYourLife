#pragma once
#include "../shapes/shape.h"
#include "pdf.h"


struct scatterRecord
{
    ray specularRay;
    bool isSpecular;
    vec3 albedo;
    pdf* pdf;

    scatterRecord() :
        isSpecular(false) {}
};

class material
{
public:
    virtual bool scatter(
        const ray& r,
        const intersection& hit,
        scatterRecord& srec) const
    {
        return false;
    };

    virtual float scatteringPdf(
        const ray& r, const intersection& hit, const ray& scattered) const
    {
        return false;
    }

    virtual vec3 emitted(const ray& r, const intersection& hit, const vec2& uv, const vec3& point) const
    {
        return vec3(0.0f);
    }
};


