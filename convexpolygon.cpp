#include "convexpolygon.h"
#include "ray.h"

#include <iostream>

namespace RayTracer {

ConvexPolygon::ConvexPolygon(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {}

std::experimental::optional<Vec3> ConvexPolygon::getIntersectionPoint(const Ray& _r) {
	std::experimental::optional<IntersectData> _intersectDataOpt = getIntersectData(_r);
	if (!_intersectDataOpt) { return std::experimental::nullopt; }
	return std::experimental::optional<Vec3>(_intersectDataOpt.value().hitPos);
}

std::experimental::optional<Vec3> ConvexPolygon::getHitNorm(const Vec3& _position) {
	for (auto plane : getPlanes()) {
		if (plane->isPointInPlane(_position)) {
			return std::experimental::optional<Vec3>(plane->getNorm());
		}
	}
	return std::experimental::nullopt;
}

std::vector<Vec3> ConvexPolygon::getBasisVectors(double u, double v) {
	return std::vector<Vec3>{Vec3(0,0,0)};
}

Vec3 ConvexPolygon::getPointOnSurface(double u, double v) {
	return Vec3(0,0,0);
}

std::experimental::optional<IntersectData> ConvexPolygon::intersect(const Ray& _r) {
	std::experimental::optional<IntersectData> _intersection = getIntersectData(_r);
	if (!_intersection) { return std::experimental::nullopt; }
	return _intersection;
}

void ConvexPolygon::addPlane(Plane * const _plane) {
	if (_plane == nullptr) { return; }
	planes.push_back(_plane);
	addChild(_plane);
}

std::vector<Plane *> ConvexPolygon::getPlanes() {
	return planes;
}

bool ConvexPolygon::isPointInsideShape(const Vec3& _point) {
	for (auto plane : getPlanes()) {
		if (!plane->isPointInsidePlane(_point)) { return false; }
	}
	return true;
}

std::experimental::optional<IntersectData> ConvexPolygon::getIntersectData(const Ray& _r) {
	bool found = false;
	double dist;
	Plane * _plane_touching = nullptr;
	Vec3 _point_touching;
	IntersectData _data;

	for (auto plane : getPlanes()) {
		std::experimental::optional<IntersectData> _dataOpt = plane->getIntersectData(_r);
		if (!_dataOpt) { continue; }
		Vec3 _point = _dataOpt.value().hitPos;

		if (!isPointInsideShape(_point)) { continue; }

		double _dist = (_point - _r.getPosition()).length();
		if (found == false || _dist < dist) {	// pick intersection closest to ray
			found = true;
			_plane_touching = plane;
			_point_touching = _point;
			_data = _dataOpt.value();
			dist = _dist;
		}
	}

	if (found) {
		return std::experimental::optional<IntersectData>(_data);
	}

	return std::experimental::nullopt;
}

std::experimental::optional<IntersectData> ConvexPolygon::getIntersectData(const Vec3& _point) {
	Ray r(getScene(), _point, Vec3(0,0,1), 1);
	return getIntersectData(r);
}

}
