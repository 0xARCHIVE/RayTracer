#include "ray.h"

Ray::Ray(const Scene& _scene, const Vec3& _position, const Vec3& _angle, int _life_left, const ColorData _colorData) {
	life_left = _life_left;
}

Vec3 Ray::computeResult() {
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
		IntersectData = scene.getIntersectData(*this);
		// TODO: compute new ray directions and spread, and spawn new rays
		Vec3 recursiveResult = Vec3(0,0,0);
		for (auto const& spawnedRay : spawnedRays) {
			recursiveResult += spawnedRay.computeResult();
		}
		return (colorData.multiplier*(colorData.emissivity*colorData.color + colorData.color.hadamard(recursiveResult)));
	}
}
