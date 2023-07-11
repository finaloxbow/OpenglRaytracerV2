
#include <glfw/glfw3.h>
#include "../common.h"

class Window : public CudaManaged {
private:
	GLFWwindow* _window;

	void processInput();

public:

	Window(uint32_t width, uint32_t height, const char* title);
	~Window();

	static void init();
	static void cleanup();

	bool is_alive();
	void update_frame();
	
};