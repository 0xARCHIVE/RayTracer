#include "box.h"

namespace RayTracer {

Box::Box(Scene* const _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions, bool _canIntersectRays, bool _canGenerateRays) : ConvexPolygon(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	dimensions = _dimensions;

	// todo: create planes and setup ConvexPolygon
}

}
