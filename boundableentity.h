#ifndef BOUNDABLEENTITY_H
#define BOUNDABLEENTITY_H

#include "entity.h"

namespace RayTracer {

class BoundingBox;
class Vec3;
class Ray;
class Surface;

class BoundableEntity : public Entity {
	protected:
		BoundingBox * boundingBox;
	public:
		BoundableEntity(Scene * const _scene, const Vec3& _position, const Vec3& _angle);
		virtual ~BoundableEntity();
		void setAngle(const Vec3& _angle);
		void setPosition(const Vec3& _position);
		void addChild(Surface * const _surface);
		virtual std::vector<Vec3> getMaxCoords() const = 0;
		void refreshBoundingBox();
		BoundingBox * getBoundingBox();
		bool hasBoundingBox() const;
		bool doesRayHit(const Ray& r) const;
};

}

#endif
