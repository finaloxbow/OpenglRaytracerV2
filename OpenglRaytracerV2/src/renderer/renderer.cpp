#include "renderer.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stdexcept>

Renderer::Renderer()
{
    _framebuffer_size = WINDOW_WIDTH * WINDOW_HEIGHT * NUM_CHANNELS;
    _framebuffer = new GLubyte[_framebuffer_size];
	_texture_id = 0;
	_framebuffer_id = 0;

    framebuffer_setup();
}

void Renderer::init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw new std::runtime_error("opengl init failed");
    }
}

void Renderer::framebuffer_setup()
{
	//data alignment stuff
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	//texture creation
	glGenTextures(1, &_texture_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture_id);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		_framebuffer
	);

	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//generates texture mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//creates framebuffer and attaches previous texture to it
	glGenFramebuffers(1, &_framebuffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer_id);
	glFramebufferTexture(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		_texture_id,
		0
	);

	
}

void Renderer::update_frame()
{
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		0,
		0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		_framebuffer
	);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, _framebuffer_id);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void Renderer::update_pixel(uint64_t x, uint64_t y, glm::vec4& rgba)
{
	if (x < WINDOW_HEIGHT && y < WINDOW_WIDTH) {
		auto red = rgba.x;
		auto green = rgba.y;
		auto blue = rgba.z;
		auto alpha = rgba.t;

		_framebuffer[x * WINDOW_WIDTH * NUM_CHANNELS + y * NUM_CHANNELS + 0] = static_cast<int>(256 * clamp(red, 0.0f, 0.999f));
		_framebuffer[x * WINDOW_WIDTH * NUM_CHANNELS + y * NUM_CHANNELS + 1] = static_cast<int>(256 * clamp(green, 0.0f, 0.999f));
		_framebuffer[x * WINDOW_WIDTH * NUM_CHANNELS + y * NUM_CHANNELS + 2] = static_cast<int>(256 * clamp(blue, 0.0f, 0.999f));
		_framebuffer[x * WINDOW_WIDTH * NUM_CHANNELS + y * NUM_CHANNELS + 3] = static_cast<int>(256 * clamp(alpha, 0.0f, 0.999f));
	}
}
