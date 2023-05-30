#pragma once

#include "../material.h"

class Lambertian : public Material {
public:
	Lambertian(glm::vec3& a);
	virtual bool scatter(
		Ray& r,
		HitRecord& rec,
		glm::vec3& attenuation,
		Ray& scattered
	) override;

private:
	glm::vec3 albedo;
};