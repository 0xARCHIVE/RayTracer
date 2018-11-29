#ifndef RAY_H
#define RAY_H

#include "colordata.h"

#include <memory>

namespace RayTracer {

class RayFactory;
class Vec3;
class Scene;

class Ray {
	private:
		Scene * scene;
		std::shared_ptr<RayFactory> rayfactory;

		Vec3 worldPos;
		Vec3 worldDir;

		int life_left;
		ColorData color;
	public:
		Ray(Scene * scene, const Vec3 &worldPos, const Vec3 &worldDir, int life_left);
		Ray(Scene * scene, const Vec3 &worldPos, const Vec3 &worldDir, int life_left, ColorData color);

		inline Vec3 getPos() const { return this->worldPos; }
		inline Vec3 getDirection() const { return this->worldDir; }
		inline int lifeLeft() const { return this->life_left; }

		Vec3 computeResult();
};

}

#endif
