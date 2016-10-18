#pragma once
#include "../common/types.h"
#include "../common/random.h"

class perlin
{
public:
    static float trilinearInterpolation(float c[2][2][2], float u, float v, float w);
    static float trilinearVectorInterpolation(vec3 c[2][2][2], float u, float v, float w);
    static float noise(const vec3& point);
    static float turbulence(const vec3& p, int depth = 7);
    static void permute(int* p, int n);
    static vec3* generate();
    static int* generatePerm();

public:
    static vec3* ranvec;
    static int* permX;
    static int* permY;
    static int* permZ;

};