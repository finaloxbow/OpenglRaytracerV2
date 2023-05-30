#pragma once

#include <glm/glm.hpp>

#include "../ray/ray.h"
#include "../hittable_objects/hittable_list/hittable_list.h"
#include "../hittable_objects/sphere/sphere.h"

constexpr uint32_t max_recursion_depth = 10;

class Scene {
private:
	HittableList world;

	glm::vec3 calculate_collision(Ray& r, int depth);

public:
	Scene();

	glm::vec3 calculate_collision(Ray& r);
};