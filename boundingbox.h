#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "box.h"
#include "surface.h"

namespace RayTracer {

class BoundingBox : public Box {
	public:
		BoundingBox(Scene * const _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions);
};

}

#endif
