#include "camera.h"

#include "../src/common.h"

#include <glm/glm.hpp>

#include <iostream>


Camera::Camera(float vfov, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp)
: _cameraPos(camPos), _cameraFront(camFront), _cameraUp(camUp), _fov(degrees_to_radians(vfov)) {
	updateCamVectors();
}

void Camera::updateCamVectors()
{
	auto h = tan(_fov / 2.0f);
	float viewport_height = 2.0f * h;
	float viewport_width = ASPECT_RATIO * viewport_height;

	glm::vec3 w = glm::normalize(_cameraFront);
	glm::vec3 u = glm::normalize(glm::cross(_cameraUp, w));
	glm::vec3 v = glm::cross(w, u);

	_horizontal = viewport_width * u;
	_vertical = viewport_height * v;
	_lowerLeftCorner = _cameraPos
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
	glm::vec3 direction = _lowerLeftCorner + u * _horizontal + v * _vertical - _cameraPos;
	Ray r(_cameraPos, direction);

	return r;
}

void Camera::moveForward()
{
	_cameraPos -= camSpeed * _cameraFront;
	updateCamVectors();
}

void Camera::moveBackward()
{
	_cameraPos += camSpeed * _cameraFront;
	updateCamVectors();
}

void Camera::moveRight()
{
	_cameraPos -= camSpeed * glm::normalize(glm::cross(_cameraFront, _cameraUp));
	updateCamVectors();
}

void Camera::moveLeft()
{
	_cameraPos += camSpeed * glm::normalize(glm::cross(_cameraFront, _cameraUp));
	updateCamVectors();
}

