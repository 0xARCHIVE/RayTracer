#ifndef RAYINTERACTABLE_H
#define RAYINTERACTABLE_H

#include "entity.h"
#include "ray.h"

#include <experimental/optional>

namespace RayTracer {

class IntersectData;
class Vec3;
class Scene;

class RayInteractable : public Entity {
	protected:
		bool flag_canIntersectRays = false;
		bool flag_canGenerateRays = false;
	public:
		RayInteractable(Scene * const _scene);
		RayInteractable(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays);
		virtual std::experimental::optional<IntersectData> intersect(const Ray& _r, bool testForwards = true, bool testBackwards = false) const;
		bool canIntersectRays() const;
		bool canGenerateRays() const;
		void setIntersectRays(bool _canIntersectRays);
		void setGenerateRays(bool _canGenerateRays);
};

}

#endif
