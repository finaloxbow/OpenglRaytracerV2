#pragma once

#include "../src/camera/camera.h"
#include "../src/scene/scene.h"
#include "../src/renderer/renderer.h"

//number of samples per pixel for antialiasing
constexpr uint32_t samplesPerPixel = 3;

class RayCollider : public CudaManaged {
private:
	Camera* camera;
	Scene* scene;
	Renderer* renderer;
public:
	RayCollider(Camera* camera, Scene* scene, Renderer* renderer);

	__global__ void calculate_collisions();
};