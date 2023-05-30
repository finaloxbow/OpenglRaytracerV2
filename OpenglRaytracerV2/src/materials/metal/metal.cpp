#include "metal.h"

Metal::Metal(glm::vec3& a, float f)
: albedo(a), fuzz(f) {}

bool Metal::scatter(Ray& r, HitRecord& rec, glm::vec3& attenuation, Ray& scattered)
{
	glm::vec3 reflected = reflect(glm::normalize(r.direction()), rec.normal);
	glm::vec3 temp = reflected + fuzz * randomInUnitSphere();
	scattered = Ray(rec.point, temp);
	attenuation = albedo;
	return glm::dot(scattered.direction(), rec.normal) > 0;
}
