#include "ray.h"
#include "intersectdata.h"
#include "scene.h"
#include "consts.h"
#include "surface.h"

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

	Vec3 returnValue = colorData.multiplier*colorData.emissivity*colorData.color;
//	std::cout << life_left << " " << returnValue << std::endl;

	// if no life left, we're done
	// ask scene for intersection
	// 	if none, we're done
	// life == 1:
	// 	add colordata from surface and don't spawn new rays
	// life >= 1:
	// 	combine colordata from surface and the results of spawnedRays computeResult()
	if (life_left <= 0) { return returnValue; }

	std::experimental::optional<IntersectData> intersectData = scene->getIntersectData(*(this));
	if (!intersectData) { return returnValue; }	// didn't hit anything

	Vec3 _hitPos = intersectData.value().hitPos;
	Vec3 _hitNorm = intersectData.value().hitNorm;
	if (_hitNorm.dot(getDirection()) > 0) {  _hitNorm = -1*_hitNorm; }

	ColorData _colorData = intersectData.value().colorData;
	const Surface * _surface = intersectData.value().surface;
	Vec3 secondary_result(0,0,0);

	if (_surface->canGenerateRays()) {
		ColorData _colorData_reflected = _colorData;
		_colorData_reflected.multiplier = colorData.reflectivity;

		ColorData _colorData_transmitted = _colorData;
		_colorData_transmitted.multiplier = colorData.transmissivity;

		Vec3 _direction_reflected = -1*((2*getDirection().dot(_hitNorm)*_hitNorm) - getDirection());
//		std::vector<Ray> _rays_reflected = generateRays(_hitPos, _direction_reflected, lifeLeft() - 1, _colorData_reflected, GLOBAL_SETTING_RAY_SPREAD, GLOBAL_SETTING_RAY_NUM_SPAWN);
		std::vector<Ray> _rays_reflected = generateRays(_hitPos + 2*GLOBAL_SETTING_RAY_PRECISION*_hitNorm, _direction_reflected, lifeLeft() - 1, _colorData_reflected, GLOBAL_SETTING_RAY_SPREAD*(1.0 - _colorData_reflected.reflectivity), GLOBAL_SETTING_RAY_NUM_SPAWN);

		secondary_result += computeRayResult(_rays_reflected); // todo: join transmitted rays and pass to function
		// TODO: transmitted ray direction and spawning
	}

	returnValue += colorData.multiplier*colorData.color.hadamard(secondary_result);
	return returnValue;
}

Vec3 Ray::getDirection() const {
	return getAngle();
}

}
