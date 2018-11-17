#ifndef BOX_H
#define BOX_H

#include "convexpolygon.h"
#include "ray.h"
#include "vec3.h"

#include <experimental/optional>

namespace RayTracer {

class Box : public ConvexPolygon {
	protected:
		Vec3 dimensions;
	public:
		Box(Scene * const _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions, bool _canIntersectRays, bool _canGenerateRays);
};

}

#endif
