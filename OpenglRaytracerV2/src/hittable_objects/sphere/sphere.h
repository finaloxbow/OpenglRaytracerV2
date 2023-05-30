#pragma once

#include "../hittable.h"

#include <glm/glm.hpp>

#include <memory>

class Sphere : public Hittable {
public:
	Sphere(glm::vec3 center, float r, std::shared_ptr<Material> m);

	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) override;

private:
	glm::vec3 center;
	float radius;
	std::shared_ptr<Material> mat_ptr;
};