#include "plane.h"
#include "entity.h"

#include <iostream>

namespace RayTracer {

Plane::Plane(Scene * const _scene, const Vec3& _position, const Vec3& _norm, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, Vec3(0,0,0), _canIntersectRays, _canGenerateRays) {
	norm = _norm.normalised();
}

std::experimental::optional<Vec3> Plane::getIntersectionPoint(const Ray& _r) {
	//TODO
	return std::experimental::nullopt;
}

std::experimental::optional<Vec3> Plane::getHitNorm(const Vec3& _position) {
	// TODO
	return std::experimental::nullopt;
}

bool Plane::isPointInPlane(const Vec3& _point) const {
	if ((_point - getPosition()).dot(norm) <= 0.0001) { return true; }
	return false;
}

}
