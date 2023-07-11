#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../src/common.h"

class Renderer : public CudaManaged {
private:
	GLubyte* _framebuffer;
	uint64_t _framebuffer_size;
	uint32_t _framebuffer_id;
	uint32_t _texture_id;
public:

	Renderer();

	static void init();

	void framebuffer_setup();
	void update_frame();
	__device__ void update_pixel(uint64_t x, uint64_t y, glm::vec3& rgba);

};