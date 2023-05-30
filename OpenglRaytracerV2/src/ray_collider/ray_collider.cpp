#include "ray_collider.h"

#include "../common.h"

RayCollider::RayCollider(Camera* camera, Scene* scene, Renderer* renderer)
: camera(camera), scene(scene), renderer(renderer) {}

void RayCollider::calculate_collisions()
{
	for (int x = 0; x < WINDOW_HEIGHT; x++) {
		for (int y = 0; y < WINDOW_WIDTH; y++) {
			glm::vec3 pixelColor(0, 0, 0);

			for (int s = 0; s < samplesPerPixel; s++) {
				Ray r = camera->get_ray_at_coords(x, y, true);
				pixelColor += scene->calculate_collision(r);
			}

			float scale = 1.0f / samplesPerPixel;
			//pixelColor *= scale;
			pixelColor.x = sqrt(scale * pixelColor.x);
			pixelColor.y = sqrt(scale * pixelColor.y);
			pixelColor.z = sqrt(scale * pixelColor.z);

			glm::vec4 rgbaColor(pixelColor.x, pixelColor.y, pixelColor.z, 1.0f);
			renderer->update_pixel(x, y, rgbaColor);
		}
	}
}
