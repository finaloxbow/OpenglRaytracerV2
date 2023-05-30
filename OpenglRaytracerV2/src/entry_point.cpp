#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "../src/common.h"
#include "../src/window/window.h"
#include "../src/renderer/renderer.h"
#include "../src/camera/camera.h"
#include "../src/scene/scene.h"
#include "../src/ray_collider/ray_collider.h"

int main() {
	
	Window::init();
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	
	Renderer::init();
	Renderer renderer;

	Camera camera;
	Scene scene;
	RayCollider collider(&camera, &scene, &renderer);
	collider.calculate_collisions();

	while (window.is_alive()) {
		renderer.update_frame();
		window.update_frame();
	}

	Window::cleanup();

	return 0;
}