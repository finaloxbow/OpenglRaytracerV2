#include "scene.h"

#include "../common.h"

glm::vec3 Scene::calculate_collision(Ray& r, int depth)
{
    HitRecord rec;
    
    if (depth <= 0) return glm::vec3(0, 0, 0);

    if (world.hit(r, 0.0001, infinity, rec)) {
        glm::vec3 target = rec.point + rec.normal + randomInUnitSphere();
        glm::vec3 direction = target - rec.point;
        Ray tmp(rec.point, direction);
        return 0.5f * calculate_collision(tmp, depth - 1);
    }

    glm::vec3 unit_dir = glm::normalize(r.direction());
    float t = 0.5f * (unit_dir.y + 1.0f);
    return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

Scene::Scene()
{
    world.add(std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(glm::vec3(0, -100.5f, -1), 100));
}


glm::vec3 Scene::calculate_collision(Ray& r)
{   
    return calculate_collision(r, max_recursion_depth);
}
