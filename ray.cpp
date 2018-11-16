#include "ray.h"
#include "intersectdata.h"
#include "scene.h"

#include <experimental/optional>

namespace RayTracer {

Ray::Ray(Scene * const _scene, const Vec3& _position, const Vec3& _direction, int _life_left, ColorData _colorData) : RayGenerator(_scene, _position, _direction) {
	life_left = _life_left;
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
		// TODO: compute new ray directions and spread, and spawn new rays
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
