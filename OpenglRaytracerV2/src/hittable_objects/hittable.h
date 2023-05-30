#pragma once

#include "../ray/ray.h"
#include <glm/glm.hpp>

struct HitRecord {
	glm::vec3 point;
	glm::vec3 normal;
	float t;
	bool front_face;

	inline void set_face_normal(Ray& r, glm::vec3& outwardNormal) {
		front_face = glm::dot(r.direction(), outwardNormal) < 0;
		normal = front_face ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) = 0;
};