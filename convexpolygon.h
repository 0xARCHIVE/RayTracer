#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include "surface.h"
#include "plane.h"
#include "vec3.h"

#include <vector>
#include <experimental/optional>

namespace RayTracer {

class ConvexPolygon : public Surface {
	protected:
		std::vector<Plane *> planes;
	public:
		ConvexPolygon(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays);
		std::experimental::optional<Vec3> getIntersectionPoint(const Ray& _r);
		std::experimental::optional<Vec3> getHitNorm(const Vec3& _position);
		std::experimental::optional<IntersectData> getIntersectData(const Ray& _r);
		std::vector<Vec3> getBasisVectors(float u, float v);
		Vec3 getPointOnSurface(float u, float v);
		std::experimental::optional<IntersectData> intersect(const Ray& _r);
		void addPlane(Plane * const _plane);
		std::vector<Plane *> getPlanes();
		bool isPointInsideShape(const Vec3& _point);
};

}

#endif
