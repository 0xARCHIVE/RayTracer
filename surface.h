#ifndef SURFACE_H
#define SURFACE_H

#include "entity.h"
#include "rayinteractable.h"

#include <functional>

namespace RayTracer {

class Surface : public Entity, public RayInteractable {
	protected:
		std::function<ColorData(const Vec3&)> colorDataFunc;
	public:
		Surface(const Scene& _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Entity(_scene, _position, _angle) : RayInteractable(_canIntersectRays, _canGenerateRays);
		virtual Vec3 getIntersectionPoint(const Ray& _r) = 0;
		ColorData getColorData(const Vec3& _position);
		virtual Vec3 getHitNorm(const Vec3& _position) = 0;
};

}

#endif
