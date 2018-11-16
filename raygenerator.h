#ifndef RAYGENERATOR_H
#define RAYGENERATOR_H

#include "entity.h"
#include "colordata.h"
#include "ray.h"

#include <vector>

namespace RayTracer {

class RayGenerator : public Entity {
	protected:
		std::vector<Ray> spawnedRays;
	public:
		RayGenerator(const Scene& _scene) : Entity(_scene, Vec3(0,0,0), Vec3(0,0,0)) {};	// position and angle not important for generator
		Ray generateRay(const Vec3& _position, const Vec3& _direction, int _life_left, const ColorData& _colorData);
		std::vector<Ray>& generateRays(const Vec3& _position, const Vec3& _direction, int _life_left, const ColorData& _colorData, float _spreadAngle, int num_rays);
};

}

#endif
