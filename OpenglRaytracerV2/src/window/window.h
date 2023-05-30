
#include <glfw/glfw3.h>

class Window {
private:
	GLFWwindow* _window;

public:

	Window(uint32_t width, uint32_t height, const char* title);
	~Window();

	static void init();
	static void cleanup();

	bool is_alive();
	void update_frame();
};