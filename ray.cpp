#include "ray.h"
#include "intersectdata.h"
#include "scene.h"
#include "consts.h"

#include <experimental/optional>

namespace RayTracer {

Ray::Ray(Scene * const _scene, const Vec3& _position, const Vec3& _direction, int _life_left) : RayGenerator(_scene, _position, _direction) {
	life_left = _life_left;
}

Ray::Ray(Scene * const _scene, const Vec3& _position, const Vec3& _direction, int _life_left, ColorData _colorData) : RayGenerator(_scene, _position, _direction) {
	colorData = _colorData;
	life_left = _life_left;
}

int Ray::lifeLeft() {
	return life_left;
}

Vec3 Ray::computeResult() {
	// need to be in a scene
	if (scene == nullptr) { return Vec3(0,0,0); }

	// if no life left, we're done
	// ask scene for intersection
	// 	if none, we're done
	// life == 1:
	// 	add colordata from surface and don't spawn new rays
	// life >= 1:
	// 	combine colordata from surface and the results of spawnedRays computeResult()
	if (life_left < 1) {
		return Vec3(0,0,0);
	} else if (life_left == 1) {
		return colorData.color*colorData.emissivity*colorData.multiplier;
	} else {
		std::experimental::optional<IntersectData> intersectData = scene->getIntersectData(*(this));
		if (!intersectData) { return Vec3(0,0,0); }	// didn't hit anything

		ColorData _colorData = intersectData.value().colorData;
		Vec3 _hitPos = intersectData.value().hitPos;
		Vec3 _hitNorm = intersectData.value().hitNorm;

		ColorData _colorData_reflected = _colorData;
		_colorData_reflected.multiplier = _colorData.reflectivity;

		ColorData _colorData_transmitted = _colorData;
		_colorData_transmitted.multiplier = _colorData.transmissivity;

		Vec3 _direction_reflected = (2*getDirection().dot(_hitNorm)*_hitNorm) - getDirection();
		std::vector<Ray> _rays_reflected = generateRays(_hitPos, _direction_reflected, lifeLeft() - 1, _colorData_reflected, GLOBAL_SETTING_RAY_SPREAD, GLOBAL_SETTING_RAY_NUM_SPAWN);

		// TODO: transmitted ray direction and spawning

		Vec3 recursiveResult = Vec3(0,0,0);
		for (auto & spawnedRay : spawnedRays) {
			recursiveResult += spawnedRay.computeResult();
		}
		return (colorData.multiplier*(colorData.emissivity*colorData.color + colorData.color.hadamard(recursiveResult)));
	}
}

Vec3 Ray::getDirection() const {
	return getAngle();
}

}
