#pragma once

#include "../material.h"
#include "../src/common.h"
#include <glm/glm.hpp>

class Metal : public Material {
public:
	Metal(glm::vec3& a, float f);
	virtual bool scatter(
		Ray& r,
		HitRecord& rec,
		glm::vec3& attenuation,
		Ray& scattered
	) override;


private:
	glm::vec3 albedo;
	float fuzz;
};