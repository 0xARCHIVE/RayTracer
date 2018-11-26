#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "entity.h"
#include "rayinteractable.h"

#include <experimental/optional>

namespace RayTracer {

class Ray;
class Vec3;
class IntersectData;

class BoundingBox : public RayInteractable {
	protected:
		Vec3 dimensions;
		Vec3 min;
		Vec3 max;

	public:
		BoundingBox(Scene * const _scene, const Vec3& _position,  const Vec3& _dimensions);
		virtual ~BoundingBox();

		void setPosition(const Vec3& _position);
		Vec3 getDimensions() const;
		void setDimensions(const Vec3& _dimensions);
		bool testIntersection(const Ray& r, bool testForwards = true, bool testBackwards = false);
		void expand(BoundingBox * const bb);
		int longestAxis() const;
		BoundingBox * copy() const;
		virtual std::vector<Vec3> getMaxCoords() const;
		virtual std::experimental::optional<IntersectData> intersect(const Ray& r, bool testForwards = true, bool testBackwards = false) const override;
};

}

#endif
