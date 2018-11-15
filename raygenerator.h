#ifndef RAYGENERATOR_H
#define RAYGENERATOR_H

#include "ray.h"
#include "vec3d.h"
#include "colordata.h"

namespace RayTracer {

class RayGenerator {
	public:
		Ray spawnRay(Vec3D position, Vec3D direction, int max_recursion_depth, ColorData c, float spread);
};

}

#endif
