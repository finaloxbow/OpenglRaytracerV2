#pragma once

#include "../src/camera/camera.h"
#include "../src/scene/scene.h"
#include "../src/renderer/renderer.h"

//number of samples per pixel for antialiasing
constexpr uint32_t samplesPerPixel = 1;

class RayCollider {
private:
	Camera* camera;
	Scene* scene;
	Renderer* renderer;
public:
	RayCollider(Camera* camera, Scene* scene, Renderer* renderer);

	void calculate_collisions();
};