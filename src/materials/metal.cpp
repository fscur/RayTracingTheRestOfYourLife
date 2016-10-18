#include "metal.h"
#include "../samplers/sampler.h"
#include "../math/vmath.h"

metal::metal(texture* albedo, float roughness) :
    _albedo(albedo),
    _roughness(roughness)
{
    if (_roughness > 1.0f)
        _roughness = 1.0f;
}

bool metal::scatter(const ray& r, const intersection& hit, scatterRecord& srec) const
{
    vec3 reflectionDirection = vMath::reflect(normalize(r.direction), hit.normal);
    srec.specularRay = ray(hit.point, reflectionDirection + _roughness * sampler::randomPositionInUnitSphere(), r.time);
    srec.albedo = _albedo->fetch(hit.uv, hit.point);
    srec.isSpecular = true;
    srec.pdf = nullptr;
    return true;
}
