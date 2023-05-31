#pragma once

#include "../ray/ray.h"
#include "../common.h"

#include <glm/glm.hpp>

#include <vector>

const float camSpeed = 0.05f;

class Camera {
private:
	glm::vec3 _cameraPos;
	glm::vec3 _cameraFront;
	glm::vec3 _cameraUp;

	glm::vec3 _horizontal;
	glm::vec3 _vertical;
	glm::vec3 _lowerLeftCorner;

	//stored in radians
	float _fov;

	void updateCamVectors();

public:
	Camera(float vfov, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp);

	Ray get_ray_at_coords(uint64_t x, uint64_t y, bool addRandomOffset);

	void moveForward();
	void moveBackward();
	void moveRight();
	void moveLeft();
};