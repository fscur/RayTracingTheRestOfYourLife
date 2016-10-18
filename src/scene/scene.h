#pragma once
#include <vector>
#include <functional>
#include "../math/ray.h"
#include "../math/intersection.h"
#include "../shapes/shape.h"
#include "../shapes/shapeList.h"
#include "../accelerators/bvh.h"
#include "camera.h"

class scene
{
public:
    static scene* cornelBoxScene();

public:
    scene(camera* camera, std::function<vec3(const ray&)> getBackgroundFunction);
    void addShape(shape* shape);
    void buildBvh();
    bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const;

    camera* getCamera() const { return _camera; }
    shapeList* getImportanceShapes() const { return _importanceShapes; }
    vec3 getBackground(const ray& ray) const { return _getBackgroundFunction(ray); }

private:
    std::vector<shape*> _shapes;
    bvh _bvh;
    camera* _camera;
    std::function<vec3(const ray&)> _getBackgroundFunction;
    shapeList* _importanceShapes;
};


