#pragma once

#include <glm/glm.hpp>
#include "../common.h"

class Ray : public CudaManaged {
private:
	glm::vec3 orig, dir;

public:
	Ray(glm::vec3 origin, glm::vec3 direction);

	glm::vec3 origin();
	void set_origin(glm::vec3 origin);
	glm::vec3 direction();
	void set_direction(glm::vec3 direction);
	glm::vec3 at(float t) const;
};