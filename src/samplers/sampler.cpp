#include "sampler.h"
#include "../common/random.h"

vec3 sampler::randomPositionInUnitSphere()
{
    vec3 randomPosition;
    do
    {
        float x = random::next();
        float y = random::next();
        float z = random::next();

        randomPosition = 2.0f * vec3(x, y, z) - 1.0f;

    } while (dot(randomPosition, randomPosition) >= 1.0f);

    return normalize(randomPosition);
}

vec3 sampler::randomPositionInDisk()
{
    vec3 randomPosition;
    do
    {
        float x = random::next();
        float y = random::next();

        randomPosition = 2.0f * vec3(x, y, 0.0f) - vec3(1.0f, 1.0f, 0.0f);

    } while (dot(randomPosition, randomPosition) >= 1.0f);

    return randomPosition;
}

vec3 sampler::randomCosineDirection()
{
    float r1 = random::next();
    float r2 = random::next();
    float z = sqrt(1.0f - r2);
    float φ = 2.0f * π * r1;
    float x = cos(φ) * 2.0f * sqrt(r2);
    float y = sin(φ) * 2.0f * sqrt(r2);

    return vec3(x, y, z);
}

vec3 sampler::randomToSphere(float radius, float distanceSquared) 
{
    float r1 = random::next();
    float r2 = random::next();
    float z = 1.0f + r2 * (sqrt(1.0f - radius*radius / distanceSquared) - 1.0f);
    float φ = 2.0f * π * r1;
    float x = cos(φ) * sqrt(1.0f - z*z);
    float y = sin(φ) * sqrt(1.0f - z*z);
    return vec3(x, y, z);
}