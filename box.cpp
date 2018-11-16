#include "box.h"

namespace RayTracer {

Box::Box(Scene* const _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	dimensions = _dimensions;
}

std::experimental::optional<Vec3> Box::getIntersectionPoint(const Ray& _r) {
	// TODO
	return std::experimental::nullopt;
}

std::experimental::optional<Vec3> Box::getHitNorm(const Vec3& _position) {
	// TODO
	return std::experimental::nullopt;
}

}
