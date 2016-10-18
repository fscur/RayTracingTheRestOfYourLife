#pragma once
#define _CRT_RAND_S
#include <stdlib.h>
#include <cstdlib>
#include <random>
#include "types.h"

class random
{
public:
    static float next() 
    {
        static thread_local std::mt19937 generator;
        std::uniform_real_distribution<float>distribution(0.0, 1.0);
        return distribution(generator);
    }
};