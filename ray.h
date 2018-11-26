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
		std::shared_ptr<Scene> scene;
		std::shared_ptr<RayFactory> rayfactory;

		Vec3 worldPos;
		Vec3 worldDir;

		int life_left;
		ColorData color;
	public:
		Ray(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldDir, int life_left);
		Ray(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldDir, int life_left, ColorData color);

		Vec3 getPos() const;
		Vec3 getDirection() const;
		int lifeLeft();

		Vec3 computeResult();
};

}

#endif
