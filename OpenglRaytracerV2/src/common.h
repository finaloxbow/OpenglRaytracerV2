#pragma once

#include <cmath>
#include <limits>

//window settings
constexpr uint64_t WINDOW_WIDTH = 1280;
constexpr uint64_t WINDOW_HEIGHT = 720;
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
		if (glm::dot(p, p) >= 1) continue;
		return p;
	}

	return glm::vec3(0, 0, 0);
}