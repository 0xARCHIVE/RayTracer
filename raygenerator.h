#ifndef RAYGENERATOR_H
#define RAYGENERATOR_H

#include "entity.h"
#include "colordata.h"
#include "vec3.h"

#include <vector>

namespace RayTracer {

class Ray;
class RayGenerator : public Entity {
	public:
		RayGenerator(Scene * const _scene);
		RayGenerator(Scene * const _scene, const Vec3& _position, const Vec3& _angle);
		Ray generateRay(const Vec3& _position, const Vec3& _direction, int _life_left, const ColorData& _colorData) const;
		std::vector<Ray> generateRays(const Vec3& _position, const Vec3& _direction, int _life_left, const ColorData& _colorData, double _spreadAngle, int num_rays) const;
		Vec3 computeRayResult(std::vector<Ray> rays) const;
};

}

#endif
