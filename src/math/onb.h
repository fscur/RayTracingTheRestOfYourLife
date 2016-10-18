#pragma once

#include "../common/types.h"

class onb
{
public:
    onb();
    onb(vec3 direction);

    vec3 transform(const vec3& a) const;

public:
    vec3 u;
    vec3 v;
    vec3 w;
};