#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "intersectdata.h"
#include "vec3.h"

#include <experimental/optional>
#include <vector>
#include <memory>

namespace RayTracer {

class Ray;
class Entity;

class BoundingBox {
	private:
		Vec3 dimensions;
		Vec3 minCorner;
		Vec3 maxCorner;
		Vec3 worldPos;

	public:
		BoundingBox(const Vec3 &worldPos = Vec3(0,0,0),  const Vec3 &dimensions = Vec3(0,0,0));

		void setPos(const Vec3 &worldPos);
		Vec3 getPos() const;

		Vec3 getDimensions() const;
		void setDimensions(const Vec3 &dimensions);

		std::vector<Vec3> getCorners() const;
		void setCorners(const Vec3 &v1, const Vec3 &v2);

		int getLongestAxis() const;
		void expandToInclude(const BoundingBox &aabb);
		void expandToInclude(const Vec3 &corner1, const Vec3 &corner2);
		void expandToInclude(const std::vector<std::shared_ptr<Entity>>& ents);
		void copy(const BoundingBox &aabb);

		std::unique_ptr<IntersectData> intersectRay(const Ray &r) const;
};

}

#endif
