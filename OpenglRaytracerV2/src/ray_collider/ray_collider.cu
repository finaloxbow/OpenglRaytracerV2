#include "ray_collider.h"

#include "../common.h"
#include "../ray/ray.h"

RayCollider::RayCollider(Renderer* renderer)
: renderer(renderer) {}

__device__ float hit_sphere(glm::vec3 center, float radius, Ray* ray) {
	//A = ray origin
	//b = direction
	//c = center

	glm::vec3 oc = ray->origin() - center;
	float a = glm::length2(ray->direction());
	float b = 2.0f * glm::dot(ray->direction(), oc);
	float c = glm::length2(oc) - radius * radius;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return -1;
	else
		//pick closer intersection pt, so minus
		return (-b - sqrt(discriminant)) / (2.0f * a);
}

__device__ glm::vec3 shoot_ray(Ray* ray) {
	float t = hit_sphere(glm::vec3(0, 0, -1), 0.5f, ray);
	if (t > 0.0f) {
		glm::vec3 n = glm::normalize(ray->at(t) - glm::vec3(0, 0, -1));
		return 0.5f * glm::vec3(n.x + 1, n.y + 1, n.z + 1);
	}
	
	glm::vec3 dir = glm::normalize(ray->direction());
	t = (dir.y + 1.0f) / 2.0f;
	return (1.0f - t) * glm::vec3(1, 1, 1) + t * glm::vec3(167.0f / 256.0f, 65.0f / 256.0f, 240 / 256.0f);
}

__global__ void collider_kernel(Renderer* renderer) {
	int row = blockDim.x * blockIdx.x + threadIdx.x;
	int col = blockDim.y * blockIdx.y + threadIdx.y;

	if (row >= WINDOW_HEIGHT || col >= WINDOW_WIDTH) return;

	float viewport_height = 2.0f;
	float viewport_width = viewport_height * ASPECT_RATIO;
	float focal_length = 1.0f;

	glm::vec3 origin(0, 0, 0);
	glm::vec3 horizontal(viewport_width, 0, 0);
	glm::vec3 vertical(0, viewport_height, 0);
	glm::vec3 lower_left_corner = glm::vec3(0, 0, -focal_length) - (horizontal / 2.0f) - (vertical / 2.0f);
	
	float u = float(col) / (WINDOW_WIDTH - 1);
	float v = float(row) / (WINDOW_HEIGHT - 1);

	Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	glm::vec3 color = shoot_ray(&ray);
	renderer->update_pixel(row, col, color);
}

void RayCollider::calculate_collisions()
{
	int tx = 8, ty = 8;
	dim3 blocks(WINDOW_HEIGHT / tx + 1, WINDOW_WIDTH / ty + 1);
	dim3 threads(tx, ty);

	collider_kernel<<<blocks, threads>>>(renderer);
	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());
}

