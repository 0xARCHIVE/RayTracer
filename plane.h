#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

#include <vector>
#include <experimental/optional>

namespace RayTracer {

class Plane : public Surface {
	protected:
		Vec3 norm;
	public:
		Plane(Scene * const _scene, const Vec3& _norm, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays);
		std::experimental::optional<Vec3> getIntersectionPoint(const Ray& _r);
		std::experimental::optional<Vec3> getHitNorm(const Vec3& _point);
		std::vector<Vec3> getBasisVectors(float u, float v);
		Vec3 getPointOnSurface(float u, float v);
		float distToPlane(const Vec3& _point) const;
		float signedDistToPlane(const Vec3& _point) const;
		bool isPointInsidePlane(const Vec3& _point) const;
		bool isPointInPlane(const Vec3& _point) const;
};

}

#endif
