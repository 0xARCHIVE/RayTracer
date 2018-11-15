#ifndef SURFACE_H
#define SURFACE_H

#include "entity.h"
#include "rayinteractable.h"

namespace RayTracer {

class Surface : public Entity, public RayInteractable {
	public:
		Surface(const Scene& scene, const Vec3& position, const Vec3& angle, bool canIntersectRays, bool canGenerateRays);
		virtual Vec3 getIntersectionPoint(const Ray& r) = 0;
		virtual ColorData getColorData(const Vec3& position) = 0;
		virtual Vec3 getHitNorm(const Vec3& position) = 0;
};

}

#endif
