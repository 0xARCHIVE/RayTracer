#include "ray.h"
#include "scene.h"
#include "surface.h"
#include "consts.h"
#include "intersectdata.h"
#include "rayfactory.h"

#include <experimental/optional>

namespace RayTracer {

Ray::Ray(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldDir, int life_left) {
	this->scene = scene;
	this->rayfactory = std::make_shared<RayFactory>(scene);
	this->life_left = life_left;
	this->worldPos = worldPos;
	this->worldDir = worldDir;
}

Ray::Ray(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldDir, int life_left, ColorData color) {
	this->scene = scene;
	this->rayfactory = std::make_shared<RayFactory>(scene);
	this->life_left = life_left;
	this->worldPos = worldPos;
	this->worldDir = worldDir;
	this->color = color;
}

Vec3 Ray::getPos() const {
	return this->worldPos;
}

Vec3 Ray::getDirection() const {
	return this->worldDir;
}

int Ray::lifeLeft() {
	return this->life_left;
}

Vec3 Ray::computeResult() {
	if (scene == nullptr) { return Vec3(0,0,0); }

	Vec3 returnValue = this->color.multiplier*this->color.emissivity*this->color.color;

	if (life_left <= 0) { return returnValue; }
	std::experimental::optional<IntersectData> intersectData = this->scene->intersectRay(*(this));
	if (!intersectData) { return returnValue; }

	Vec3 hitPos = intersectData.value().hitPos;
	Vec3 hitNorm = intersectData.value().hitNorm;
	if (hitNorm.dot(getDirection()) > 0) {  hitNorm = -1*hitNorm; }

	ColorData color = intersectData.value().colorData;
	const Surface * surface = intersectData.value().surface;
	Vec3 secondary_result(0,0,0);

	if (surface->canGenerateRays()) {
		ColorData color_reflected = color;
		color_reflected.multiplier = this->color.reflectivity;

		ColorData color_transmitted = color;
		color_transmitted.multiplier = this->color.transmissivity;

		Vec3 direction_reflected = -1*((2*this->getDirection().dot(hitNorm)*hitNorm) - this->getDirection());
//		std::vector<Ray> _rays_reflected = generateRays(_hitPos, _direction_reflected, lifeLeft() - 1, _colorData_reflected, GLOBAL_SETTING_RAY_SPREAD, GLOBAL_SETTING_RAY_NUM_SPAWN);
		std::vector<std::shared_ptr<Ray>> rays_reflected = this->rayfactory->generateRays(hitPos + 2*GLOBAL_SETTING_RAY_PRECISION*hitNorm, direction_reflected, this->lifeLeft() - 1, color_reflected, GLOBAL_SETTING_RAY_SPREAD*(1.0 - color_reflected.reflectivity), GLOBAL_SETTING_RAY_NUM_SPAWN);

		for (auto ray : rays_reflected) {
			secondary_result += (1.0/rays_reflected.size())*ray->computeResult();
		}
		// TODO: transmitted ray direction and spawning
	}

	returnValue += color.multiplier*color.color.hadamard(secondary_result);
	return returnValue;
}

}
