#ifndef RAYFACTORY_H
#define RAYFACTORY_H

namespace RayTracer {

class RayFactory {
	private:
		std::shared_ptr<const Scene> scene;

	public:
		RayFactory();

		std::unique_ptr<Ray> generateRay(const Vec3 &worldPos, const Vec3 &worldDir, int life_left, const ColorData &c) const;
		std::vector<std::unique_ptr<Ray>> generateRays(const Vec3 &worldPos, const Vec3 &worldDir, int life_left, const ColorData &c, double spreadAng, int numRays) const;
};

}

#endif
