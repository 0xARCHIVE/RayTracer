#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

#include <vector>
#include <experimental/optional>

namespace RayTracer {

class Plane : public Surface {
	public:
		Plane(Scene * const _scene, const Vec3& _norm, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays);
		std::experimental::optional<Vec3> getIntersectionPoint(const Ray& _r);
		std::experimental::optional<Vec3> getHitNorm(const Vec3& _point);
		std::experimental::optional<IntersectData> intersect(const Ray& _r);
		std::vector<Vec3> getBasisVectors(float u, float v);
		Vec3 getPointOnSurface(float u, float v);
		float distToPlane(const Vec3& _point) const;
		float signedDistToPlane(const Vec3& _point) const;
		bool isPointInsidePlane(const Vec3& _point) const;
		bool isPointInPlane(const Vec3& _point) const;
		Vec3 getNorm();
		std::experimental::optional<IntersectData> getIntersectData(const Ray& _r);
};

}

#endif
