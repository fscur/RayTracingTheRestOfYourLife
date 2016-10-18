#include "perlin.h"

vec3* perlin::ranvec = perlin::generate();
int* perlin::permX= perlin::generatePerm();
int* perlin::permY= perlin::generatePerm();
int* perlin::permZ= perlin::generatePerm();

float perlin::trilinearInterpolation(float c[2][2][2], float u, float v, float w)
{
    float accum = 0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                accum +=
                (i * u + (1 - i) * (1 - u)) *
                (j * v + (1 - j) * (1 - v)) *
                (k * w + (1 - k) * (1 - w)) * c[i][j][k];

    return accum;
}

float perlin::trilinearVectorInterpolation(vec3 c[2][2][2], float u, float v, float w)
{
    float uu = u*u * (3 - 2 * u);
    float vv = v*v * (3 - 2 * v);
    float ww = w*w * (3 - 2 * w);
    float accum = 0;

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
            {
                vec3 weight(u - i, v - j, w - k);

                accum +=
                    (i * uu + (1 - i) * (1 - uu)) *
                    (j * vv + (1 - j) * (1 - vv)) *
                    (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight);
            }

    return accum;
}

float perlin::noise(const vec3 & point)
{
    float u = point.x - floor(point.x);
    float v = point.y - floor(point.y);
    float w = point.z - floor(point.z);

    int i = floor(point.x);
    int j = floor(point.y);
    int k = floor(point.z);

    vec3 c[2][2][2];

    for (int di = 0; di < 2; ++di)
        for (int dj = 0; dj < 2; ++dj)
            for (int dk = 0; dk < 2; ++dk)
            {
                c[di][dj][dk] =
                    ranvec[
                        permX[(i + di) & 255] ^
                            permY[(j + dj) & 255] ^
                            permZ[(k + dk) & 255]];

            }

    return trilinearVectorInterpolation(c, u, v, w);
}

float perlin::turbulence(const vec3 & p, int depth)
{
    float accum = 0;
    vec3 temp_p = p;
    float weight = 1.0;
    for (int i = 0; i < depth; i++) {
        accum += weight*noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }
    return fabs(accum);
}

vec3 * perlin::generate()
{
    vec3* p = new vec3[256];
    for (int i = 0; i < 256; ++i)
    {
        auto dir = vec3(
            -1.0f + 2.0f * random::next(),
            -1.0f + 2.0f * random::next(),
            -1.0f + 2.0f * random::next());

        p[i] = normalize(dir);
    }

    return p;
}

void perlin::permute(int * p, int n)
{
    for (int i = n - 1; i > 0; --i)
    {
        int target = int(random::next()*(i + 1));
        int temp = p[i];
        p[i] = p[target];
        p[target] = temp;
    }
}

int * perlin::generatePerm()
{
    int* p = new int[256];
    for (int i = 0; i < 256; ++i)
        p[i] = i;

    permute(p, 256);
    return p;
}
