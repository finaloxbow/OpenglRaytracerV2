#pragma once

#include "../hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
	HittableList();
	HittableList(std::shared_ptr<Hittable> object);

	void clear();
	void add(std::shared_ptr<Hittable> object);

	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) override;

private:
	std::vector<std::shared_ptr<Hittable>> objects;
};
