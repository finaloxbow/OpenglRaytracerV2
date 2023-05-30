#pragma once

#include "../hittable.h"

#include <glm/glm.hpp>

class Sphere : public Hittable {
public:
	Sphere(glm::vec3 center, float r);

	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) override;

private:
	glm::vec3 center;
	float radius;
};