#include "raygenerator.h"
#include "ray.h"
#include "consts.h"

#include <iostream>

namespace RayTracer {

RayGenerator::RayGenerator(Scene * const _scene) : Entity(_scene, Vec3(0,0,0), Vec3(0,0,0)) {}

RayGenerator::RayGenerator(Scene * const _scene, const Vec3& _position, const Vec3& _angle) : Entity(_scene, _position, _angle) {}

Ray RayGenerator::generateRay(const Vec3& _position, const Vec3& _direction, int _life_left, const ColorData& _colorData) const {
	return generateRays(_position, _direction, _life_left, _colorData, 0, 1).front();
}

std::vector<Ray> RayGenerator::generateRays(const Vec3& _position, const Vec3& _direction, int _life_left, const ColorData& _colorData, double _spreadAngle, int num_rays) const {
	std::vector<Ray> newRays;
	if (scene == nullptr) { return newRays; }
	for (int i = 0; i < num_rays; i++) {
		Vec3 newDirection = _direction.randomSpread(_spreadAngle);
		Ray newRay(scene, _position, newDirection, _life_left, _colorData);
		newRays.push_back(newRay);
	}
	return newRays;
}

Vec3 RayGenerator::computeRayResult(std::vector<Ray> rays) const {
	Vec3 recursiveResult = Vec3(0,0,0);
	for (auto & spawnedRay : rays) {
		recursiveResult += spawnedRay.computeResult()*(1.0/rays.size());
	}
	return recursiveResult;
}

}
