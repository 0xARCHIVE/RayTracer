#ifndef RAY_H
#define RAY_H

namespace RayTracer {

class Ray {
	private:
		std::shared_ptr<const Scene> scene;
		RayFactory rayfactory;

		Vec3 worldPos;
		Vec3 worldDir;

		int life_left;
		ColorData color;
	public:
		Ray(std::shared_ptr<const Scene> scene, const Vec3 &worldPos, const Vec3 & worldDir, int _life_left);
		Ray(std::shared_ptr<const Scene> scene, const Vec3 &worldPos, const Vec3 & worldDir, int _life_left, ColorData color);

		Vec3 getDirection() const;
		int lifeLeft();

		Vec3 computeResult();
};

}

#endif
