#include "plane.h"
#include "entity.h"
#include "consts.h"

#include <algorithm>
#include <iostream>
#include <cmath>

namespace RayTracer {

Plane::Plane(Scene * const _scene, const Vec3& _position, const Vec3& _angle, double _width, double _height, bool _canIntersectRays = true, bool _canGenerateRays = true) : Surface(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	setDimensions(_width, _height);
}

std::experimental::optional<IntersectData> Plane::getIntersectData(const Ray& _r, bool testForwards = true, bool testBackwards = false) {
	std::experimental::optional<Vec3> _intersectPointOpt = getIntersectionPoint(_r, testForwards, testBackwards);
	if (!_intersectPointOpt) { return std::experimental::nullopt; }

	IntersectData _intersectData;
	_intersectData.surface = this;
	_intersectData.hitPos = _intersectPointOpt.value();
	_intersectData.colorData = getColorData(_intersectData.hitPos);
	_intersectData.hitNorm = getNorm();

	return std::experimental::optional<IntersectData>(_intersectData);
}

std::experimental::optional<Vec3> Plane::getIntersectionPoint(const Ray& _r, bool testForwards = true, bool testBackwards = false) {
	Vec3 _point = _r.getPosition();
	Vec3 _direction = _r.getDirection();

	if (isPointInPlane(_point)) { return std::experimental::optional<Vec3>(_point); }

	double numerator = signedDistToPlane(_point);
	double denominator = _direction.dot(getNorm());
	if (denominator == 0) { return std::experimental::nullopt; }

	double lambda = numerator/denominator;
	Vec3 hitPos = _point + lambda*_direction;

	Vec3 dV = (hitPos - _r.getPosition());
	double _dot = dV.dot(_r.getDirection());

	if (!testForwards && _dot > 0) { return std::experimental::nullopt; }
	if (!testBackwards && _dot < 0) { return std::experimental::nullopt; }

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

void Plane::setDimensions(double _width, double _height) {
	width = _width;
	height = _height;
}

double Plane::getWidth() const {
	return width;
}

double Plane::getHeight() const {
	return height;
}

std::vector<Vec3> Plane::getMaxCoords() const {
	// return two corners of BB enclosing plane
	Vec3 corner1 = toWorld(Vec3(width,height,0));
	Vec3 corner2 = toWorld(Vec3(width,-height,0));
	Vec3 corner3 = toWorld(Vec3(-width,height,0));
	Vec3 corner4 = toWorld(Vec3(-width,-height,0));

	double maxX = std::max( std::max(corner1.getX(),corner2.getX()), std::max(corner3.getX(),corner4.getX()) );
	double maxY = std::max( std::max(corner1.getY(),corner2.getY()), std::max(corner3.getY(),corner4.getY()) );
	double maxZ = std::max( std::max(corner1.getZ(),corner2.getZ()), std::max(corner3.getZ(),corner4.getZ()) );

	double minX = std::min( std::min(corner1.getX(),corner2.getX()), std::min(corner3.getX(),corner4.getX()) );
	double minY = std::min( std::min(corner1.getY(),corner2.getY()), std::min(corner3.getY(),corner4.getY()) );
	double minZ = std::min( std::min(corner1.getZ(),corner2.getZ()), std::min(corner3.getZ(),corner4.getZ()) );

	return std::vector<Vec3>{ Vec3(maxX,maxY,maxZ), Vec3(minX,minY,minZ) };
}

}

