#include "../samplers/sampler.h"
#include "../math/onb.h"
#include "cosinePdf.h"
#include "lambertian.h"

lambertian::lambertian(texture* albedo) :
    _albedo(albedo)
{
}

float lambertian::scatteringPdf(
    const ray& r, const intersection& hit, const ray& scattered) const
{
    float cosine = dot(hit.normal, normalize(scattered.direction));

    if (cosine < 0.0f)
        cosine = 0.0f;

    return cosine * π¯¹;
}

bool lambertian::scatter(
    const ray& r, 
    const intersection& hit, 
    scatterRecord& srec) const
{
    srec.isSpecular = false;
    srec.albedo = _albedo->fetch(hit.uv, hit.point);
    srec.pdf = new cosinePdf(hit.normal);
    return true;
}