#include "ray.h"
#include "intersectdata.h"
#include "scene.h"
#include "consts.h"

#include <iostream>
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
	if (scene == nullptr) { return Vec3(0,0,0); }

	// if no life left, we're done
	// ask scene for intersection
	// 	if none, we're done
	// life == 1:
	// 	add colordata from surface and don't spawn new rays
	// life >= 1:
	// 	combine colordata from surface and the results of spawnedRays computeResult()
	if (life_left < 1) { return Vec3(0,0,0); }

	std::experimental::optional<IntersectData> intersectData = scene->getIntersectData(*(this));
	if (!intersectData) { return Vec3(0,0,0); }	// didn't hit anything

	Vec3 _hitPos = intersectData.value().hitPos;
	Vec3 _hitNorm = intersectData.value().hitNorm;
	ColorData _colorData = intersectData.value().colorData;
	Surface * _surface = intersectData.value().surface;

	if (_surface->canGenerateRays() && life_left > 1) {
		ColorData _colorData_reflected = _colorData;
		_colorData_reflected.multiplier = colorData.reflectivity;

		ColorData _colorData_transmitted = _colorData;
		_colorData_transmitted.multiplier = colorData.transmissivity;

		Vec3 _direction_reflected = (2*getDirection().dot(_hitNorm)*_hitNorm) - getDirection();
		std::vector<Ray> _rays_reflected = generateRays(_hitPos, _direction_reflected, lifeLeft() - 1, _colorData_reflected, GLOBAL_SETTING_RAY_SPREAD, GLOBAL_SETTING_RAY_NUM_SPAWN);

		// TODO: transmitted ray direction and spawning
	}

	Vec3 secondary_result = computeRayResult();
	//std::cout << colorData.color << "*" << secondary_result << "=" << colorData.color.hadamard(secondary_result) << std::endl;
	//std::cout << colorData.multiplier << " " << colorData.emissivity << std::endl;
	return (colorData.multiplier* (colorData.emissivity*colorData.color + colorData.color.hadamard(secondary_result)) );
}

Vec3 Ray::getDirection() const {
	return getAngle();
}

}
