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
	
	Camera camera(45.0f, glm::vec3(2, 2, -1), glm::vec3(2, 2, 0), glm::vec3(0, 1, 0));

	Window::init();
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, &camera);
	
	Renderer::init();
	Renderer renderer;

	Scene scene;
	RayCollider collider(&camera, &scene, &renderer);
	
	while (window.is_alive()) {
		collider.calculate_collisions();
		renderer.update_frame();
		window.update_frame();
	}

	Window::cleanup();

	return 0;
}