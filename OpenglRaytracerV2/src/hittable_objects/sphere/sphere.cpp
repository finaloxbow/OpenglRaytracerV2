#include "sphere.h"

#include <glm/gtx/norm.hpp>

Sphere::Sphere(glm::vec3 center, float r, std::shared_ptr<Material> m)
:center(center), radius(r), mat_ptr(m) {}

bool Sphere::hit(Ray& r, float tMin, float tMax, HitRecord& rec)
{
    glm::vec3 oc = r.origin() - center;
    float a = glm::length2(r.direction());
    auto half_b = glm::dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - radius*radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) return false;

    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd) / a;
    if (root < tMin || tMax < root) {
        root = (-half_b + sqrtd) / a;
        if (root < tMin || tMax < root) return false;
    }

    rec.t = root;
    rec.point = r.at(rec.t);
    glm::vec3 outwardNormal = (rec.point - center) / radius;
    rec.set_face_normal(r, outwardNormal);
    rec.mat_ptr = mat_ptr;

    return true;
}
