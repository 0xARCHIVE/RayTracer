#include "plane.h"
#include "entity.h"
#include "consts.h"

#include <iostream>
#include <cmath>

namespace RayTracer {

Plane::Plane(Scene * const _scene, const Vec3& _position, const Vec3& _norm, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, Vec3(0,0,0), _canIntersectRays, _canGenerateRays) {
	norm = _norm.normalised();
}

std::experimental::optional<Vec3> Plane::getIntersectionPoint(const Ray& _r) {
	Vec3 _point = _r.getPosition();
	Vec3 _direction = _r.getDirection();
	float numerator = signedDistToPlane(_point);
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

std::vector<Vec3> Plane::getBasisVectors(float u, float v) {
	auto nonzero_sign = [](float _x) {
		if (_x > 0) return 1;
		if (_x < 0) return -1;
		return 1;
	};

	Vec3 s;
	Vec3 t;

	// see https://math.stackexchange.com/a/1180076/221755
	if (norm.getY() == 0) {
		float _y = nonzero_sign(norm.getY());

		s.setX(0);
		s.setY(_y);
		s.setZ(0);

		t.setX(-1*norm.getZ()*_y);
		t.setY(0);
		t.setZ(norm.getX()*_y);

	} else {
		float _x = nonzero_sign(-1*( pow(norm.getX(),2)/norm.getY() + norm.getY() ));

		s.setX(_x);
		s.setY(-1*(norm.getX()/norm.getY())*_x);
		s.setZ(0);

		t.setX(-1*(norm.getX()*norm.getZ()/norm.getY())*_x);
		t.setY(-1*norm.getZ()*_x);
		t.setZ(-1*(pow(norm.getX(),2)/norm.getY())*_x + -1*norm.getY()*_x);
	}

	return std::vector<Vec3>{t.normalised(),s.normalised()};
}

Vec3 Plane::getPointOnSurface(float u, float v) {
	std::vector<Vec3> basis = getBasisVectors(u, v);
	Vec3 _point = u*basis[0] + v*basis[1] + getPosition();
	return _point;
}

float Plane::distToPlane(const Vec3& _point) const {
	return abs(signedDistToPlane(_point));
}

float Plane::signedDistToPlane(const Vec3& _point) const {
	return (getPosition() - _point).dot(norm);
}

bool Plane::isPointInsidePlane(const Vec3& _point) const {
	// "inside" plane if it's on the opposite side to the outward pointing norm
	if (signedDistToPlane(_point) >= -GLOBAL_SETTING_RAY_PRECISION) { return true; }
	return false;
}

bool Plane::isPointInPlane(const Vec3& _point) const {
	if (distToPlane(_point) <= GLOBAL_SETTING_RAY_PRECISION) { return true; }
	return false;
}

Vec3 Plane::getNorm() {
	return norm;
}

}

