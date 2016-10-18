#pragma once
#include "../common/types.h"
#include "../math/ray.h"
#include "../math/rectangle.h"
#include "../scene/scene.h"
#include "../scene/camera.h"
#include "../io/pixelWriter.h"

struct pathTracerRunInfo
{
    rectangle<int> tile;
    int width;
    int height;
    int ssp;
    float k;
};

class pathTracer
{
public:
    pathTracer(scene* scene);
    ~pathTracer();
    void setScene(scene* scene);
    void run(const pathTracerRunInfo& info, pixelWriter* pixelWriter);
    void cancel();

private:
    vec3 li(const ray& r, int depth);
    vec3 deNaN(const vec3& color);

private:
    bool _running;
    scene* _scene;
    camera* _camera;
};