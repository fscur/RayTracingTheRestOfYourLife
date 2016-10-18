#pragma once
#include "../common/types.h"
#include "../common/random.h"
#include "../math/onb.h"
#include "../samplers/sampler.h"
#include "../shapes/shape.h"

class pdf
{
public:
    virtual float value(const vec3& direction) const = 0;
    virtual vec3 generate() const = 0;
};



