#pragma once

#include "../ray/ray.h"
#include "../common.h"
#include "../materials/material.h"
#include <glm/glm.hpp>

#include <memory>

class Material;

struct HitRecord {
	glm::vec3 point;
	glm::vec3 normal;
	std::shared_ptr<Material> mat_ptr;
	float t;
	bool front_face;

	inline void set_face_normal(Ray& r, glm::vec3& outwardNormal) {
		front_face = glm::dot(r.direction(), outwardNormal) < 0;
		normal = front_face ? outwardNormal : -outwardNormal;
	}
};

class Hittable : public CudaManaged {
public:
	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) = 0;
};