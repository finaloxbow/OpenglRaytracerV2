#include "camera.h"

#include "../src/common.h"

#include <glm/glm.hpp>

Camera::Camera()
{
	float aspect_ratio = ((float)WINDOW_WIDTH) / WINDOW_HEIGHT;
	float viewport_height = 2.0f;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0f;

	_origin = glm::vec3(0, 0, 0);
	_horizontal = glm::vec3(viewport_width, 0, 0);
	_vertical = glm::vec3(0, viewport_height, 0);
	_lowerLeftCorner =
		_origin
		- (0.5f * _horizontal)
		- (0.5f * _vertical)
		- glm::vec3(0, 0, focal_length);
}

Ray Camera::get_ray_at_coords(uint64_t x, uint64_t y, bool addRandomOffset)
{
	float offsetU = addRandomOffset ? randomFloat() : 0.0f;
	float offsetV = addRandomOffset ? randomFloat() : 0.0f;

	float u = (((float)y) + offsetU) / (WINDOW_WIDTH - 1);
	float v = (((float)x) + offsetV) / (WINDOW_HEIGHT - 1);
	glm::vec3 direction = _lowerLeftCorner + u * _horizontal + v * _vertical - _origin;
	Ray r(_origin, direction);

	return r;
}

