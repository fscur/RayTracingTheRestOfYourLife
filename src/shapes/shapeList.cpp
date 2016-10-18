#include "shapeList.h"
#include "../common/random.h"

bool shapeList::hit(const ray & r, float tMin, float tMax, intersection & hit) const
{
    intersection tempRecord;
    bool hitAnything = false;
    double closestHit = tMax;
    auto listCount = _shapes.size();

    for (int i = 0; i < listCount; ++i)
    {
        if (_shapes[i]->hit(r, tMin, closestHit, tempRecord))
        {
            hitAnything = true;
            closestHit = tempRecord.t;
            hit = tempRecord;
        }
    }

    return hitAnything;
}

bool shapeList::createBoundingBox(float t0, float t1, aabb & a) const
{
    if (_shapes.size() < 1)
        return false;
    aabb temp_box;

    bool first_true = _shapes[0]->createBoundingBox(t0, t1, temp_box);
    if (!first_true)
        return false;
    else
        a = temp_box;

    for (int i = 1; i < _shapes.size(); ++i)
    {
        if (_shapes[0]->createBoundingBox(t0, t1, temp_box))
        {
            a = aabb::getSurroundingAabb(a, temp_box);
        }
        else
        {
            return false;
        }
    }
    return true;
}

float shapeList::pdfValue(const vec3 & o, const vec3 & v) const
{
    auto listSize = _shapes.size();
    float weight = 1.0f / float(listSize);
    float sum = 0;

    for (int i = 0; i < listSize; i++)
        sum += weight*_shapes[i]->pdfValue(o, v);

    return sum;
}

vec3 shapeList::random(const vec3 & o) const
{
    int s = _shapes.size();
    float t = random::next();
    //std::cout << std::to_string(s) << " " << std::to_string(t) << std::endl;
    int index = int(t * s);
    if (index > s - 1)
        index = s - 1;

    return _shapes[index]->random(o);
}

void shapeList::add(shape * shape)
{
    _shapes.push_back(shape);

}
