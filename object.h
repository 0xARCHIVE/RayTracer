#ifndef OBJECT_H
#define OBJECT_H

#include "boundableentity.h"

#include <vector>
#include <experimental/optional>

namespace RayTracer {

class BoundingBox;
class IntersectData;
class Surface;
class Vec3;

class Object : public BoundableEntity {
	protected:
		std::vector<Surface *> surfaces;
	public:
		Object(Scene * const _scene, const Vec3& _position, const Vec3& _angle);
		virtual ~Object();
		void addSurface(Surface* _surface);
		std::vector<Surface *>& getSurfaces();
		virtual std::vector<Vec3> getMaxCoords() const;
		std::experimental::optional<IntersectData> intersect(const Ray& _r, bool testForwards = true, bool testBackwards = false) const;
};

}

#endif

