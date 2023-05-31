#pragma once

#include <glm/glm.hpp>

#include "../ray/ray.h"
#include "../hittable_objects/hittable_list/hittable_list.h"
#include "../hittable_objects/sphere/sphere.h"

constexpr uint32_t max_recursion_depth = 25;

class Scene {
private:
	HittableList world;

public:
	Scene();

	glm::vec3 calculate_collision(Ray& r);
};