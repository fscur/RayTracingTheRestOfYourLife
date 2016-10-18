#include "isotropic.h"

isotropic::isotropic(texture * albedo) :
    _albedo(albedo)
{
}

bool isotropic::scatter(const ray & r, const intersection & hit, scatterRecord & srec) const
{
    srec.isSpecular = true;
    srec.specularRay = ray(hit.point, sampler::randomPositionInUnitSphere(), r.time);
    srec.albedo = _albedo->fetch(hit.uv, hit.point);
    srec.pdf = nullptr;
    return true;
}
