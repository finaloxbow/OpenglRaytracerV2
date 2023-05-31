#include "window.h"

void Window::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void Window::cleanup()
{
	glfwTerminate();
}

Window::Window(uint32_t width, uint32_t height, const char* title, Camera* camera)
: camera(camera) {
	_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(0);
}

Window::~Window()
{
	glfwDestroyWindow(_window);
}

bool Window::is_alive()
{
	return !glfwWindowShouldClose(_window);
}

void Window::update_frame()
{
	processInput();
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void Window::processInput()
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(_window, true);
	}
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->moveForward();
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->moveBackward();
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->moveLeft();
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->moveRight();
	}
}
