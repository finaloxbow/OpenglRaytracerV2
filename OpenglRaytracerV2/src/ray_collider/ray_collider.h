#pragma once

#include "../src/renderer/renderer.h"

class RayCollider : public CudaManaged {
private:
	Renderer* renderer;
public:
	RayCollider(Renderer* renderer);

	void calculate_collisions();
};