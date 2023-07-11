#pragma once

#include <glm/glm.hpp>
#include "../common.h"

class Ray : public CudaManaged {
private:
	glm::vec3 orig, dir;

public:
	__device__ Ray(glm::vec3 origin, glm::vec3 direction);

	__device__ glm::vec3 origin();
	__device__ glm::vec3 direction();
	__device__ glm::vec3 at(float t) const;
};