#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

#include <vector>
#include <experimental/optional>

namespace RayTracer {

class Plane : public Surface {
	protected:
		double width;
		double height;
	public:
		Plane(Scene * const _scene, const Vec3& _position, const Vec3& _angle, double _width, double _height, bool _canIntersectRays = true, bool _canGenerateRays = true);

		std::experimental::optional<Vec3> getIntersectionPoint(const Ray& _r, bool testForwards = true, bool testBackwards = false) const;
		virtual std::experimental::optional<Vec3> getHitNorm(const Vec3& _point) const override;
		virtual std::vector<Vec3> getBasisVectors(double u, double v) const override;
		virtual Vec3 getPointOnSurface(double u, double v);
		virtual std::experimental::optional<IntersectData> getIntersectData(const Ray& _r, bool testForwards = true, bool testBackwards = false) const override;

		double distToPlane(const Vec3& _point) const;
		double signedDistToPlane(const Vec3& _point) const;
		bool isPointInsidePlane(const Vec3& _point) const;
		bool isPointInPlane(const Vec3& _point) const;
		Vec3 getNorm() const;

		void setDimensions(double width, double height);
		double getWidth() const;
		double getHeight() const;
		std::vector<Vec3> getMaxCoords() const override;
};

}

#endif
