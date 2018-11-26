#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

namespace RayTracer {

class ConvexPolygon : public Surface {
	private:
		std::vector<std::shared_ptr<Plane>> planes;

	public:
		ConvexPolygon(std::shared_ptr<const Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng);
		virtual ~ConvexPolygon();

		virtual Vec3 getPointOnSurface(double u, double v) const override;
		virtual std::experimental::optional<Vec3> getNorm(const Vec3 &worldPos) const override;
		virtual std::experimental::optional<IntersectData> intersectRay(const Ray &r) const override;

		virtual std::vector<Vec3> getCorners() const override;

		void addPlane(std::shared_ptr<Plane> plane);
		std::vector<std::shared_ptr<Plane>> getPlanes() const;

		bool isInsideShape(const Vec3 &worldPos) const;
};

}

#endif
