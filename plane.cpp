#include "plane.h"
#include "entity.h"
#include "consts.h"

#include <iostream>
#include <cmath>

namespace RayTracer {

Plane::Plane(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {}

std::experimental::optional<IntersectData> Plane::intersect(const Ray& _r) {
	return getIntersectData(_r);
}

std::experimental::optional<IntersectData> Plane::getIntersectData(const Ray& _r) {
	std::experimental::optional<Vec3> _intersectPointOpt = getIntersectionPoint(_r);
	if (!_intersectPointOpt) { return std::experimental::nullopt; }

	IntersectData _intersectData;
	_intersectData.surface = this;
	_intersectData.hitPos = _intersectPointOpt.value();
	_intersectData.colorData = getColorData(_intersectData.hitPos);
	_intersectData.hitNorm = getNorm();

	return std::experimental::optional<IntersectData>(_intersectData);
}

std::experimental::optional<Vec3> Plane::getIntersectionPoint(const Ray& _r) {
	Vec3 _point = _r.getPosition();
	Vec3 _direction = _r.getDirection();

	if (isPointInPlane(_point)) { return std::experimental::optional<Vec3>(_point); }

	double numerator = signedDistToPlane(_point);
	double denominator = _direction.dot(getNorm());
	if (denominator == 0) { return std::experimental::nullopt; }

	double lambda = numerator/denominator;
	Vec3 hitPos = _point + lambda*_direction;

//	std::cout << "Ray " << _point << " " << _direction << " hit plane at " << hitPos << " with dist " << numerator << std::endl;

	return std::experimental::optional<Vec3>(hitPos);
}

std::experimental::optional<Vec3> Plane::getHitNorm(const Vec3& _point) {
	if (isPointInPlane(_point)) { return std::experimental::optional<Vec3>(getNorm()); }
	return std::experimental::nullopt;
}

std::vector<Vec3> Plane::getBasisVectors(double u, double v) {
	return std::vector<Vec3>{forward(),right()};
}

Vec3 Plane::getPointOnSurface(double u, double v) {
	std::vector<Vec3> basis = getBasisVectors(u, v);
	Vec3 _point = toWorld(Vec3(u,v,0));
	return _point;
}

double Plane::distToPlane(const Vec3& _point) const {
	return abs(signedDistToPlane(_point));
}

double Plane::signedDistToPlane(const Vec3& _point) const {
	return (getPosition() - _point).dot(getNorm());
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

Vec3 Plane::getNorm() const {
	return up();
}

}

