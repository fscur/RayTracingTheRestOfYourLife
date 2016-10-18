#include "sphere.h"

sphere::sphere(vec3 center, float radius, material* material) :
    _center(center),
    _radius(radius),
    _material(material)
{
}

bool sphere::hit(const ray& ray, float tMin, float tMax, intersection& hit) const
{
    vec3 oc = ray.origin - _center;

    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - _radius * _radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0.0f)
    {
        float temp = (-b - sqrt(discriminant)) / a;

        if (temp < tMax && temp > tMin)
        {
            hit.t = temp;
            hit.point = ray.pointAtParameter(temp);
            hit.normal = (hit.point - _center) / _radius;
            hit.material = _material;
            hit.uv = getUv(hit.normal);
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;

        if (temp < tMax && temp > tMin)
        {
            hit.t = temp;
            hit.point = ray.pointAtParameter(temp);
            hit.normal = (hit.point - _center) / _radius;
            hit.material = _material;
            hit.uv = getUv(hit.normal);
            return true;
        }
    }

    return false;
}

bool sphere::createBoundingBox(float t0, float t1, aabb& a) const
{
    vec3 r = vec3(_radius, _radius, _radius);
    a = aabb(_center - r, _center + r);
    return true;
}

float sphere::pdfValue(const vec3 & o, const vec3 & v) const
{
    intersection tempHit;

    if (this->hit(ray(o, v), 0.001f, MAX_FLOAT, tempHit))
    {
        auto p = (_center - o);
        float cos_theta_max = sqrt(1.0f - _radius*_radius / dot(p, p));
        float solid_angle = 2.0f * π * (1.0f - cos_theta_max);
        return  1.0f / solid_angle;
    }
    else
        return 0.0f;
}

vec3 sphere::random(const vec3 & o) const
{
    vec3 direction = _center - o;
    float distanceSquared = dot(direction, direction);
    onb uvw(direction);
    return uvw.transform(sampler::randomToSphere(_radius, distanceSquared));
}

vec2 sphere::getUv(const vec3& point) const
{
    float φ = atan2(point.z, point.x);
    float θ = asin(point.y);
    float u = 1.0f - (φ + π) / π_times_2;
    float v = (θ + π_over_2) / π;
    return vec2(u, v); 
}
