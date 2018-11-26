#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

namespace RayTracer {

class BoundingBox {
	private:
		Vec3 dimensions;
		Vec3 minCorner;
		Vec3 maxCorner;

	public:
		BoundingBox(const Vec3 &worldPos,  const Vec3 &dimensions);

		void setPos(const Vec3 &worldPos);

		Vec3 getDimensions() const;
		void setDimensions(const Vec3 &dimensions);

		std::vector<Vec3> getCorners() const;

		int getLongestAxis() const;
		void expandToInclude(const BoundingBox &aabb);
		void copy(const BoundingBox &aabb);

		std::experimental::optional<IntersectData> intersectRay(const Ray &r) const;
};

}

#endif
