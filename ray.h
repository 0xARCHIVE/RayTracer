#ifndef RAY_H
#define RAY_H

#include "raygenerator.h"

namespace RayTracer {

class Ray : public RayGenerator {
	protected:
		ColorData colorData;
		int life_left;
	public:
		Ray(const Scene* _scene, const Vec3& _position, const Vec3& _angle, int _life_left, const ColorData _colorData);
		Vec3 computeResult();
};

}

#endif
