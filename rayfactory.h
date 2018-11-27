#ifndef RAYFACTORY_H
#define RAYFACTORY_H

#include <memory>
#include <vector>

namespace RayTracer {

class Ray;
class Scene;
class Vec3;
class ColorData;

class RayFactory {
	private:
		Scene * scene;

	public:
		RayFactory();
		RayFactory(Scene * scene);

		void setScene(Scene * scene);

		std::shared_ptr<Ray> generateRay(const Vec3 &worldPos, const Vec3 &worldDir, int life_left, const ColorData &color, double spreadAng) const;
		std::vector<std::shared_ptr<Ray>> generateRays(const Vec3 &worldPos, const Vec3 &worldDir, int life_left, const ColorData &color, double spreadAng, int numRays) const;
};

}

#endif
