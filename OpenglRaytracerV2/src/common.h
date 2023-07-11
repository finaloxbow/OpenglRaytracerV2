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