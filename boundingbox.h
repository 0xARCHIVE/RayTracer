#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "entity.h"
#include "rayinteractable.h"

#include <experimental/optional>

namespace RayTracer {

class Ray;
class Vec3;
class IntersectData;

class BoundingBox : public Entity, public RayInteractable {
	protected:
		Vec3 dimensions;
	public:
		BoundingBox(Scene * const _scene, const Vec3& _position,  const Vec3& _dimensions);
		virtual ~BoundingBox();

		Vec3 getDimensions() const;
		void setDimensions(const Vec3& _dimensions);
		bool testIntersection(const Ray& r, bool testForwards = true, bool testBackwards = false);
		virtual std::experimental::optional<IntersectData> intersect(const Ray& r, bool testForwards = true, bool testBackwards = false);
};

}

#endif
