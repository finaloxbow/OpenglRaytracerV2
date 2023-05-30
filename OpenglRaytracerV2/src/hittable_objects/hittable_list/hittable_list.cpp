#include "hittable_list.h"

HittableList::HittableList()
{}

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
    add(object);
}

void HittableList::clear()
{
    objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
}

bool HittableList::hit(Ray& r, float tMin, float tMax, HitRecord& rec)
{
    HitRecord tempRec{};
    bool hitAnything = false;
    float closestSoFar = tMax;

    for (auto object : objects) {
        if (object.get()->hit(r, tMin, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}
