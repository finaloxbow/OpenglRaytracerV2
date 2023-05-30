#pragma once

#include "../ray/ray.h"
#include "../common.h"

#include <glm/glm.hpp>

#include <vector>

class Camera {
private:
	glm::vec3 _origin;
	glm::vec3 _lowerLeftCorner;
	glm::vec3 _horizontal;
	glm::vec3 _vertical;

public:
	Camera();

	Ray get_ray_at_coords(uint64_t x, uint64_t y, bool addRandomOffset);
};