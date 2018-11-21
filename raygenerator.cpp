#include "raygenerator.h"
#include "ray.h"

#include <iostream>

namespace RayTracer {

RayGenerator::RayGenerator(Scene * const _scene) : Entity(_scene, Vec3(0,0,0), Vec3(0,0,0)) {}

RayGenerator::RayGenerator(Scene * const _scene, const Vec3& _position, const Vec3& _angle) : Entity(_scene, _position, _angle) {}

Ray RayGenerator::generateRay(const Vec3& _position, const Vec3& _direction, int _life_left, const ColorData& _colorData) {
	return generateRays(_position, _direction, _life_left, _colorData, 0, 1).front();
}

std::vector<Ray> RayGenerator::generateRays(const Vec3& _position, const Vec3& _direction, int _life_left, const ColorData& _colorData, double _spreadAngle, int num_rays) {
	std::vector<Ray> newRays;
	if (scene == nullptr) { return newRays; }
	for (int i = 0; i < num_rays; i++) {
		// TODO: spread out rays around _direction (https://math.stackexchange.com/questions/56784/generate-a-random-direction-within-a-cone)
		Ray newRay(scene, _position, _direction, _life_left, _colorData);
		spawnedRays.push_back(newRay);
		newRays.push_back(newRay);
	}
	return newRays;
}

Vec3 RayGenerator::computeRayResult() {
	Vec3 recursiveResult = Vec3(0,0,0);
	for (auto & spawnedRay : spawnedRays) {
		recursiveResult += spawnedRay.computeResult()*(1.0/spawnedRays.size());
	}
	spawnedRays.clear();
	return recursiveResult;
}

}
