#include "../common/random.h"
#include "../shapes/sphere.h"
#include "../shapes/movingSphere.h"
#include "../materials/lambertian.h"
#include "../materials/metal.h"
#include "../materials/dielectric.h"
#include "../materials/emissive.h"
#include "../textures/colorTexture.h" 
#include "../textures/checkerTexture.h"
#include "../textures/noiseTexture.h"
#include "../textures/marbleTexture.h"
#include "../textures/imageTexture.h"
#include "../shapes/quad.h"
#include "../shapes/flipNormals.h"
#include "../shapes/box.h"
#include "../shapes/translate.h"
#include "../shapes/rotateY.h"
#include "../shapes/constantMedium.h"

#include "scene.h"

scene* scene::cornelBoxScene()
{
    auto backGroundFunction = [](const ray& ray)
    {
        return vec3(0, 1.0f, 5.0f) / 255.999f;
    };

    vec3 eye(278.0f, 278.0f, -800.0f);
    vec3 at(278.0f, 278.0, 0.0f);
    float focusDistance = 10.0f;
    float aperture = 0.0f;
    float fov = 40.0f * (π / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);

    material* red = new lambertian(new colorTexture(vec3(0.65, 0.05, 0.05)));
    material* white = new lambertian(new colorTexture(vec3(0.73, 0.73, 0.73)));
    material* green = new lambertian(new colorTexture(vec3(0.12, 0.45, 0.15)));
    material* light = new emissive(new colorTexture(vec3(15, 15, 15)));
    material* aluminum = new metal(new colorTexture(vec3(0.8, 0.85, 0.88)), 0.0f);
    material* glass = new dielectric(1.5f);

    auto greenWall = new yz_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, green);
    auto redWall = new yz_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 0.0f, red);
    auto ceilingLight = new zx_quad(rectangle<float>(213.0f, 227.0f, 130.0f, 105.0f), 554.0f, light);
    auto ceiling = new zx_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, white);
    auto floor = new zx_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 0.0f, white);
    auto backWall = new xy_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, white);
    auto sceneSphere = new sphere(vec3(165.0f, 90.0f, 165.0f), 90, glass);

    world->addShape(new flipNormals(greenWall));
    world->addShape(redWall);
    world->addShape(new flipNormals(ceiling));
    world->addShape(new flipNormals(ceilingLight));
    world->addShape(floor);
    world->addShape(new flipNormals(backWall));
    world->addShape(sceneSphere);

    auto importanceLight = new zx_quad(rectangle<float>(213.0f, 227.0f, 130.0f, 105.0f), 554.0f, 0);
    auto importanceSphere = new sphere(vec3(165.0f, 90.0f, 165.0f), 90, 0);

    shapeList* importanceList = new shapeList();
    importanceList->add(importanceSphere);
    importanceList->add(importanceLight);

    world->_importanceShapes = importanceList;

    //auto shortBox = new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 165.0f, 165.0f), white);
    auto tallBox = new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 330.0f, 165.0f), white);

    //world->addShape(new translate(new rotateY(shortBox, glm::radians(-18.0f)), vec3(130.0f, 0.0f, 65.0f)));
    world->addShape(new translate(new rotateY(tallBox, glm::radians(15.0f)), vec3(265.0f, 0.0f, 295.0f)));

    world->buildBvh();

    return world;
}

scene::scene(camera* camera, std::function<vec3(const ray&)> getBackgroundFunction) :
    _camera(camera),
    _getBackgroundFunction(getBackgroundFunction)
{
}

bool scene::hit(const ray& ray, float tMin, float tMax, intersection& hit) const
{
    return _bvh.hit(ray, tMin, tMax, hit);
}

void scene::addShape(shape* shape)
{
    _shapes.push_back(shape);
}

void scene::buildBvh()
{
    _bvh = bvh(_shapes, 0.0f, 1.0f);
}
