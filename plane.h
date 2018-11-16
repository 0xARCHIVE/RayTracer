#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

#include <experimental/optional>

namespace RayTracer {

class Plane : public Surface {
	protected:
		Vec3 norm;
	public:
		Plane(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays);
		std::experimental::optional<Vec3> getIntersectionPoint(const Ray& _r);
		std::experimental::optional<Vec3> getHitNorm(const Vec3& _position);
		bool isPointInPlane(const Vec3& _point) const;
};

}

#endif
