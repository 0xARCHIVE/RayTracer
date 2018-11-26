#ifndef SURFACE_H
#define SURFACE_H

#include "entity.h"

#include <functional>
#include <experimental/optional>

namespace RayTracer {

class Vec3;
class ColorData;
class IntersectData;
class Scene;

class Surface : public Entity {
	private:
		std::function<ColorData(const Vec3 &worldPos)> colorFunc;
		std::function<ColorData(void)> colorFunc_constant;

	public:
		Surface(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng);
		virtual ~Surface();

		ColorData getColor() const;
		ColorData getColor(const Vec3 &worldPos) const;

		void setColor(const ColorData &color);
		void setColor(std::function<ColorData(const Vec3 &worldPos)> colorFunc);

		virtual Vec3 getPointOnSurface(double u, double v) const = 0;
		virtual std::experimental::optional<Vec3> getNorm(const Vec3 &worldPos) const = 0;
};

}

#endif
