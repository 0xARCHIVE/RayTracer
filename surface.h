#ifndef SURFACE_H
#define SURFACE_H

#include "colordata.h"
#include "vec3.h"
#include "entity.h"
#include "rayinteractable.h"

#include <experimental/optional>
#include <functional>

namespace RayTracer {

class Scene;

class Surface : public Entity, public RayInteractable {
	protected:
		std::function<ColorData(const Vec3&)> colorDataFunc;
	public:
		Surface(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays);
		ColorData getColorData(const Vec3& _position);
		void setColorData(const ColorData& _colorData);
		void setColorData(std::function<ColorData(const Vec3&)> _colorDataFunc);
		virtual std::experimental::optional<Vec3> getIntersectionPoint(const Ray& _r) = 0;
		virtual std::experimental::optional<Vec3> getHitNorm(const Vec3& _position) = 0;
		std::experimental::optional<IntersectData> intersect(const Ray& _r);
};

}

#endif
