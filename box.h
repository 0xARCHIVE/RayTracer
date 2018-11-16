#ifndef BOX_H
#define BOX_H

#include "surface.h"
#include "ray.h"
#include "vec3.h"

#include <experimental/optional>

namespace RayTracer {

class Box : public Surface {
	protected:
		Vec3 dimensions;
	public:
		Box(Scene * const _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions, bool _canIntersectRays, bool _canGenerateRays);
		std::experimental::optional<Vec3> getIntersectionPoint(const Ray& _r);
		std::experimental::optional<Vec3> getHitNorm(const Vec3& _position);
};

}

#endif
