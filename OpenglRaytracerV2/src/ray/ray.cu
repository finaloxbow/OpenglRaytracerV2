#include "ray.h"

__device__ Ray::Ray(glm::vec3 origin, glm::vec3 direction)
: orig(origin), dir(direction) {}

__device__ glm::vec3 Ray::origin()
{
    return orig;
}

__device__ glm::vec3 Ray::direction()
{
    return dir;
}

__device__ glm::vec3 Ray::at(float t) const
{
    return orig + t * dir;
}
