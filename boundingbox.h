#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "entity.h"
#include "surface.h"

namespace RayTracer {

class BoundingBox {
	private:
		Surface surface;
	public:
		BoundingBox(const Scene& scene, const Vec3& position, const Vec3& angle, Surface surface);
};

}

#endif
