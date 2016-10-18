#include <iostream>
#include "../samplers/sampler.h"
#include "../common/random.h"
#include "../materials/material.h"
#include "../io/console.h"
#include "../materials/shapePdf.h"
#include "../materials/mixturePdf.h"
#include "../shapes/quad.h"

#include "pathTracer.h"

#undef max

pathTracer::pathTracer(scene* scene) :
    _running(false),
    _scene(scene),
    _camera(scene->getCamera())
{
}

pathTracer::~pathTracer()
{
}

void pathTracer::setScene(scene* scene)
{
    _scene = scene;
    _camera = scene->getCamera();
}

vec3 pathTracer::li(const ray& r, int depth)
{
    intersection hit;

    if (_scene->hit(r, 0.001f, MAX_FLOAT, hit))
    {
        scatterRecord srec;
        vec3 emitted = hit.material->emitted(r, hit, hit.uv, hit.point);

        if (depth < 50 && hit.material->scatter(r, hit, srec))
        {
            if (srec.isSpecular)
            {
                return srec.albedo * li(srec.specularRay, depth + 1);
            }
            else
            {
                shape* importanceShape = _scene->getImportanceShapes();
                shapePdf pdfLight(importanceShape, hit.point);
                mixturePdf p(&pdfLight, srec.pdf);

                ray scattered = ray(hit.point, p.generate(), r.time);
                float pdfValue = p.value(scattered.direction);
                delete srec.pdf;

                return 
                    emitted + 
                    srec.albedo * 
                    hit.material->scatteringPdf(r, hit, scattered) * 
                    li(scattered, depth+1) / pdfValue;
            }
        }
        else
            return emitted;
    }
    else
    {
        return _scene->getBackground(r);
    }
}

vec3 pathTracer::deNaN(const vec3& color) 
{
    vec3 temp = color;
    if (isnan(temp[0])) temp[0] = 0.0f;
    if (isnan(temp[1])) temp[1] = 0.0f;
    if (isnan(temp[2])) temp[2] = 0.0f;
    return temp;
}

void pathTracer::run(const pathTracerRunInfo& info, pixelWriter* pixelWriter)
{
    _running = true;
    float invSsp = 1.0f / float(info.ssp);
    float invWidth = 1.0f / float(info.width);
    float invHeight = 1.0f / float(info.height);
    
    int tileXEnd = info.tile.w + info.tile.x;
    int tileYEnd = info.tile.h + info.tile.y;

    for (int j = info.tile.y; j < tileYEnd; ++j)
    {
        float y = float(j);
        
        if (!_running)
            break;

        for (int i = info.tile.x; i < tileXEnd; ++i)
        {
            float x = float(i);

            vec3 radiance;
            for (int k = 0; k < info.ssp; ++k)
            {
                float u = (x + random::next()) * invWidth;
                float v = (y + random::next()) * invHeight;
                const ray r = _camera->castRay(vec2(u, v));
                radiance += deNaN(li(r, 0));
            }
            radiance *= invSsp;

            pixelWriter->write(x, y, sqrt(radiance.x), sqrt(radiance.y), sqrt(radiance.z));
        }
    }
}

void pathTracer::cancel()
{
    _running = false;
}
