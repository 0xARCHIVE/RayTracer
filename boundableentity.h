#ifndef BOUNDABLEENTITY_H
#define BOUNDABLEENTITY_H

#include "rayinteractable.h"

#include <memory>

namespace RayTracer {

class BoundingBox;
class Vec3;
class Ray;
class Surface;

class BoundableEntity : public RayInteractable {
	protected:
		std::unique_ptr<BoundingBox> boundingBox;
		bool enabled = false;
	public:
		BoundableEntity(std::shared_ptr<const Scene> _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays = true, bool _canGenerateRays = true);
		virtual ~BoundableEntity();
		void enableAABB();
		void setAngle(const Vec3& _angle);
		void setPosition(const Vec3& _position);
		void addChild(std::shared_ptr<Surface> _surface);
		virtual std::vector<Vec3> getMaxCoords() const;
		void refreshBoundingBox();
		void setBoundingBox(std::unique_ptr<BoundingBox> bb);
		std::unique_ptr<const BoundingBox> getBoundingBox() const;
		bool hasBoundingBox() const;
		bool doesRayHitBB(const Ray& r, bool testForwards = true, bool testBackwards = false) const;
};

}

#endif
