#ifndef RAYGENERATOR_H
#define RAYGENERATOR_H

#include "entity.h"
#include "colordata.h"
#include "ray.h"

#include <vector>

namespace RayTracer {

class RayGenerator : public Entity {
	public:
		RayGenerator(const Scene& scene);	// postion and angle not important, set to (0,0,0) in constructor
		std::vector<Ray> generateRays(const Vec3& position, const Vec3& direction, int life_left, const ColorData& colorData, float spread);
};

}

#endif
