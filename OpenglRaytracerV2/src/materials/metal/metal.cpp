#include "metal.h"

Metal::Metal(glm::vec3& a, float f)
: albedo(a), fuzz(f) {}

bool Metal::scatter(Ray& r, HitRecord& rec, glm::vec3& attenuation, Ray& scattered)
{
	glm::vec3 reflected = reflect(glm::normalize(r.direction()), rec.normal);
	scattered.set_origin(rec.point);
	glm::vec3 rand_unit = randomUnitVector();
	scattered.set_direction(reflected + fuzz * rand_unit);

	attenuation = albedo;
	return glm::dot(scattered.direction(), rec.normal) > 0;
}
