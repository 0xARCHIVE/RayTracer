#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include "surface.h"

#include <memory>
#include <vector>
#include <experimental/optional>

namespace RayTracer {

class Plane;
class Vec3;
class IntersectData;

class ConvexPolygon : public Surface {
	private:
		std::vector<std::shared_ptr<Plane>> planes;

	public:
		ConvexPolygon(const Vec3 &worldPos, const Vec3 &worldAng);
		virtual ~ConvexPolygon();

		virtual Vec3 getPointOnSurface(double u, double v) const override;
		virtual std::experimental::optional<Vec3> getNorm(const Vec3 &worldPos) const override;
		virtual std::unique_ptr<IntersectData> intersectRay(const Ray &r) const;

		void addPlane(std::shared_ptr<Plane> plane);
		std::vector<std::shared_ptr<Plane>> getPlanes() const;

		bool isInsideShape(const Vec3 &worldPos) const;
};

}

#endif
