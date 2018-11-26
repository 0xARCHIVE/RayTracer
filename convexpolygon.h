#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include "surface.h"

#include <vector>
#include <experimental/optional>

namespace RayTracer {

class Vec3;
class Plane;

class ConvexPolygon : public Surface {
	protected:
		std::vector<Plane *> planes;
	public:
		ConvexPolygon(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays = true, bool _canGenerateRays = true);
		virtual ~ConvexPolygon();

		std::experimental::optional<Vec3> getIntersectionPoint(const Ray& _r, bool testForwards, bool testBackwards);
		virtual std::experimental::optional<Vec3> getHitNorm(const Vec3& _position) const override;
		virtual std::experimental::optional<IntersectData> getIntersectData(const Vec3& _point) const;
		virtual std::experimental::optional<IntersectData> getIntersectData(const Ray& _r, bool testForwards, bool testBackwards) const override;
		virtual std::vector<Vec3> getBasisVectors(double u, double v) const override;
		virtual Vec3 getPointOnSurface(double u, double v);
		void addPlane(Plane * const _plane);
		std::vector<Plane *> getPlanes() const;
		bool isPointInsideShape(const Vec3& _point) const;

		std::vector<Vec3> getMaxCoords() const override;
};

}

#endif
