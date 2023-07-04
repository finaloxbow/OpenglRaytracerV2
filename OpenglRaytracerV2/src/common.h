#pragma once

#include <cmath>
#include <limits>
#include <iostream>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <glm/gtx/norm.hpp>

//window settings
constexpr uint64_t WINDOW_WIDTH = 1280;
constexpr uint64_t WINDOW_HEIGHT = 720;
constexpr float ASPECT_RATIO = ((float)WINDOW_WIDTH) / WINDOW_HEIGHT;
constexpr auto WINDOW_TITLE = "OpenGL Raytracer";

//number of channels for rgba
constexpr uint64_t NUM_CHANNELS = 4;

//constants
constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;

//clamps values between min and max
inline float clamp(float val, float min, float max) {
	if (val < min) return min;
	else if (val > max) return max;
	else return val;
}

inline float degrees_to_radians(float degrees) {
	return degrees * pi / 180.0f;
}

inline float randomFloat() {
	return rand() / (RAND_MAX + 1.0f);
}

inline float randomFloat(float min, float max) {
	return min + (max - min) * randomFloat();
}

inline static glm::vec3 randomVec3() {
	return glm::vec3(randomFloat(), randomFloat(), randomFloat());
}

inline static glm::vec3 randomVec3(float min, float max) {
	return glm::vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}

inline static glm::vec3 randomInUnitSphere() {
	while (true) {
		glm::vec3 p = randomVec3(-1, 1);
		if (glm::length2(p) >= 1) continue;
		return p;
	}

	return glm::vec3(0, 0, 0);
}

inline static glm::vec3 randomUnitVector() {
	return glm::normalize(randomVec3());
}

inline static bool nearZero(glm::vec3& v) {
	const float s = 1e-8f;
	return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

inline static glm::vec3 reflect(glm::vec3& v, glm::vec3& n) {
	return v - 2 * glm::dot(v, n) * n;
}

#define checkCudaErrors(val) checkCuda((val), #val, __FILE__, __LINE__)
inline void checkCuda(cudaError_t result, char* func, char* file, char* line) {
	if (result) {
		std::cerr << "CUDA error = " << static_cast<unsigned int>(result) << " at "
			<< file << ":" << line << " '" << func << "\n";

		cudaDeviceReset();
		exit(99);
	}
}

class CudaManaged {
public:
	void* operator new(size_t len) {
		void* ptr;
		cudaMallocManaged(&ptr, len);
		cudaDeviceSynchronize();
		return ptr;
	}

	void operator delete(void* ptr) {
		cudaDeviceSynchronize();
		cudaFree(ptr);
	}
};