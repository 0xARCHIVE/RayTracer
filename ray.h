#ifndef RAY_H
#define RAY_H

#include "raygenerator.h"

namespace RayTracer {

class Ray : public RayGenerator {
	private:
		ColorData colorData;
	public:
		Ray(const Scene& scene, const Vec3& position, const Vec3& angle, int life_left, const ColorData colorData);
		Vec3 computeResult();
};

}

#endif
