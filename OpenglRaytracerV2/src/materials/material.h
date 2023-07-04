#pragma once

#include "../hittable_objects/hittable.h"
#include "../ray/ray.h"
#include "../common.h"

struct HitRecord;

class Material : public CudaManaged {
public:
	virtual bool scatter(
		Ray& r,
		HitRecord& rec,
		glm::vec3& attenuation,
		Ray& scattered
	) = 0;
};