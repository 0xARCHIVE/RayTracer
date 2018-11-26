#include "rayfactory.h"
#include "ray.h"
#include "scene.h"
#include "vec3.h"

namespace RayTracer {

RayFactory::RayFactory() {}

RayFactory::RayFactory(std::shared_ptr<Scene> scene) {
	this->scene = scene;
}

std::shared_ptr<Ray> RayFactory::generateRay(const Vec3 &worldPos, const Vec3 &worldDir, int life_left, const ColorData &color, double spreadAng) const {
	return this->generateRays(worldPos, worldDir, life_left, color, spreadAng, 1)[0];
}

std::vector<std::shared_ptr<Ray>> RayFactory::generateRays(const Vec3 &worldPos, const Vec3 &worldDir, int life_left, const ColorData &color, double spreadAng, int numRays) const {
	std::vector<std::shared_ptr<Ray>> rays;
	if (this->scene == nullptr) { return rays; }
	for (int i = 0; i < numRays; i++) {
		Vec3 dir = worldDir.randomSpread(spreadAng);
		std::shared_ptr<Ray> ray = std::make_shared<Ray>(this->scene,worldPos,dir,life_left,color);
		rays.push_back(ray);
	}
	return rays;
}

}
