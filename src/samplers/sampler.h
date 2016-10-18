#pragma once
#include "../common/types.h"

class sampler
{
public:
    static vec3 randomPositionInUnitSphere();
    static vec3 randomPositionInDisk();
    static vec3 randomCosineDirection();
    static vec3 randomToSphere(float radius, float distanceSquared);
};


