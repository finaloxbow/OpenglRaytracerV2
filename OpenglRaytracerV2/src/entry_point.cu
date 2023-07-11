#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "../src/common.h"
#include "../src/window/window.h"
#include "../src/renderer/renderer.h"
#include "../src/ray_collider/ray_collider.h"

int main() {
	
	Window::init();
	Window* window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	
	Renderer::init();
	Renderer* renderer = new Renderer();

	RayCollider* collider = new RayCollider(renderer);
	
	while (window->is_alive()) {
		collider->calculate_collisions();
		renderer->update_frame();
		window->update_frame();
	}

	Window::cleanup();

	return 0;
}