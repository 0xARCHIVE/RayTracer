#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

#include <memory>
#include <experimental/optional>

namespace RayTracer {

class Scene;
class Vec3;
class Ray;
class IntersectData;

class Plane : public Surface {
	private:
		double width;
		double height;

		double distToPlane(const Vec3 &worldPos) const;
		double signedDistToPlane(const Vec3 &worldPos) const;
	public:
		Plane(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng, double width = 0, double height = 0);

		virtual Vec3 getPointOnSurface(double u, double v) const override;
		virtual std::experimental::optional<Vec3> getNorm(const Vec3 &worldPos) const override;
		virtual std::experimental::optional<IntersectData> intersectRay(const Ray &r) const override;

		virtual std::vector<Vec3> getCorners() const override;

		void setDimensions(double width, double height);
		double getWidth() const;
		double getHeight() const;

		bool isInsidePlane(const Vec3 &worldPos) const;
		bool isInPlane(const Vec3 &worldPos) const;
};

}

#endif
