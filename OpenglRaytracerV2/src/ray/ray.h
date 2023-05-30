#pragma once

#include <glm/glm.hpp>

class Ray {
private:
	glm::vec3 orig, dir;

public:

	Ray(glm::vec3& origin, glm::vec3& direction);

	glm::vec3 origin();
	glm::vec3 direction();
	glm::vec3 at(float t) const;
};