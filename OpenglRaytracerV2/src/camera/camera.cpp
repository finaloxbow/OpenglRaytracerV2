#include "camera.h"

#include "../src/common.h"

#include <glm/glm.hpp>

Camera::Camera(float vfov, glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 vup)
{
	float aspect_ratio = ((float)WINDOW_WIDTH) / WINDOW_HEIGHT;
	auto theta = degrees_to_radians(vfov);
	auto h = tan(theta / 2.0f);
	float viewport_height = 2.0f * h;
	float viewport_width = aspect_ratio * viewport_height;
	
	glm::vec3 w = glm::normalize(lookFrom - lookAt);
	glm::vec3 u = glm::normalize(glm::cross(vup, w));
	glm::vec3 v = glm::cross(w, u);

	_origin = lookFrom;
	_horizontal = viewport_width * u;
	_vertical = viewport_height * v;
	_lowerLeftCorner =
		_origin
		- (0.5f * _horizontal)
		- (0.5f * _vertical)
		- w;
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

