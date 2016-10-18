#include "../common/random.h"
#include "../math/vmath.h"

#include "dielectric.h"

dielectric::dielectric(float indexOfRefraction) :
    _indexOfRefraction(indexOfRefraction)
{}

bool dielectric::scatter(const ray& r, const intersection& hit, scatterRecord& srec) const
{
    srec.isSpecular = true;
    srec.pdf = nullptr;
    srec.albedo = vec3(1.0f, 1.0f, 1.0f);

    vec3 outwardNormal;
    vec3 reflected = vMath::reflect(r.direction, hit.normal);
    float eta;
    vec3 refracted;
    float reflectionProbability;
    float cosine;
    float incidenceAngle = dot(r.direction, hit.normal);

    if (incidenceAngle > 0.0f)
    {
        outwardNormal = -hit.normal;
        eta = _indexOfRefraction;
        cosine = _indexOfRefraction * incidenceAngle / length(r.direction);
    }
    else
    {
        outwardNormal = hit.normal;
        eta = 1.0f/_indexOfRefraction;
        cosine = -incidenceAngle / length(r.direction);
    }

    if (vMath::refract(r.direction, outwardNormal, eta, refracted))
        reflectionProbability = vMath::schlick(cosine, _indexOfRefraction);
    else
        reflectionProbability = 1.0f;

    if (random::next() < reflectionProbability)
    {
        srec.specularRay = ray(hit.point, reflected, r.time);
    }
    else
    {
        srec.specularRay = ray(hit.point, refracted, r.time);
    }

    return true;
}