#include "ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction)
: orig(origin), dir(direction) {}

glm::vec3 Ray::origin()
{
    return orig;
}

void Ray::set_origin(glm::vec3 origin)
{
    orig = origin;
}

glm::vec3 Ray::direction()
{
    return dir;
}

void Ray::set_direction(glm::vec3 direction)
{
    dir = direction;
}

glm::vec3 Ray::at(float t) const
{
    return orig + t * dir;
}
