#include "plane.h"
#include "entity.h"
#include "consts.h"

#include <iostream>

namespace RayTracer {

Plane::Plane(Scene * const _scene, const Vec3& _position, const Vec3& _norm, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, Vec3(0,0,0), _canIntersectRays, _canGenerateRays) {
	norm = _norm.normalised();
}

std::experimental::optional<Vec3> Plane::getIntersectionPoint(const Ray& _r) {
	Vec3 _point = _r.getPosition();
	Vec3 _direction = _r.getDirection();
	float numerator = (getPosition() - _point).dot(norm);
	float denominator = _direction.dot(norm);
	if (denominator == 0) {
		// ray is parallel to plane
		if (abs(numerator) <= GLOBAL_SETTING_RAY_PRECISION) {
			// ray is inside plane
			return std::experimental::optional<Vec3>(_point);
		}
		return std::experimental::nullopt;
	}

	float lambda = numerator/denominator;
	return std::experimental::optional<Vec3>(_point + lambda*_direction);
}

std::experimental::optional<Vec3> Plane::getHitNorm(const Vec3& _point) {
	if (isPointInPlane(_point)) { return std::experimental::optional<Vec3>(norm); }
	return std::experimental::nullopt;
}

float Plane::distToPlane(const Vec3& _point) const {
	return abs(_point.dot(norm));
}

bool Plane::isPointInPlane(const Vec3& _point) const {
	if (distToPlane(_point - getPosition()) <= GLOBAL_SETTING_RAY_PRECISION) { return true; }
	return false;
}

}
