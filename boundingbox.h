#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "entity.h"
#include "surface.h"

namespace RayTracer {

class BoundingBox : public Box {
	public:
		BoundingBox(const Scene& _scene, const Vec3& _position, const Vec3& _angle) : Box(_scene, _position, _angle, true, false) {}
};

}

#endif
