#ifndef RAY_H
#define RAY_H

#include "raygenerator.h"

namespace RayTracer {

class Scene;
class Ray : public RayGenerator {
	protected:
		ColorData colorData;
		int life_left;
	public:
		Ray(Scene * const _scene, const Vec3& _position, const Vec3& _direction, int _life_left, ColorData _colorData);
		Vec3 computeResult();
		Vec3 getDirection() const;
};

}

#endif
