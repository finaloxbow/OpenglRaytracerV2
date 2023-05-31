#include "scene.h"

#include "../common.h"
#include "../materials/lambertian/lambertian.h"
#include "../materials/metal/metal.h"

Scene::Scene()
{
    glm::vec3 purple_rgb(81.0f / 256.0f, 23.0f / 256.0f, 227.0f / 256.0f);
    auto purple = std::make_shared<Lambertian>(purple_rgb);
    glm::vec3 blue_rgb(31.0f / 256.0f, 199.0f / 256.0f, 255.0f / 256.0f);
    auto blue = std::make_shared<Metal>(blue_rgb, 0.5f);

    world.add(std::make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5, purple));
    world.add(std::make_shared<Sphere>(glm::vec3(0, -100.5f, -1), 100, blue));
}

//TODO: make iterative
glm::vec3 Scene::calculate_collision(Ray& r)
{   
    //return calculate_collision(r, max_recursion_depth);
    glm::vec3 curr_atten(1, 1, 1);
    Ray curr_ray = r;

    for (int depth = 0; depth < max_recursion_depth; depth++) {
        HitRecord rec;
        if (world.hit(curr_ray, 0.0001f, infinity, rec)) {
            glm::vec3 atten(0);
            Ray scattered(atten, atten);
            if (rec.mat_ptr.get()->scatter(curr_ray, rec, atten, scattered)) {
                curr_atten *= atten;
                curr_ray = scattered;
            }
            else {
                return glm::vec3(0, 0, 0);
            }
        }
        else {
            glm::vec3 unit_dir = glm::normalize(r.direction());
            float t = 0.5f * (unit_dir.y + 1.0f);
            glm::vec3 temp =  (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
            return temp * curr_atten;
        }
    }

    return glm::vec3(0, 0, 0);
}
