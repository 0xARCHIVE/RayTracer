#include "convexpolygon.h"

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

std::vector<Vec3> ConvexPolygon::getBasisVectors(float u, float v) {
	return std::vector<Vec3>{Vec3(0,0,0)};
}

Vec3 ConvexPolygon::getPointOnSurface(float u, float v) {
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
	// test all planes for "inside". If intersects one and insides all others, then we have an intersection with the surface
	bool touching = false;
	Plane * _plane_touching = nullptr;
	Vec3 _point_touching;

	for (auto plane : getPlanes()) {
		std::experimental::optional<Vec3> _pointOpt = getIntersectionPoint(_r);
		if (!_pointOpt) { continue; }	// parallel to plane, so ignore this plane

		Vec3 _point = _pointOpt.value();
		if (plane->isPointInsidePlane(_point)) {
			touching = true;
			_plane_touching = plane;
			_point_touching = _point;
		} else {
			return std::experimental::nullopt;
		}
	}

	if (touching) {
		IntersectData _intersectData;
		_intersectData.surface = _plane_touching;
		_intersectData.hitPos = _point_touching;
		_intersectData.hitNorm = _plane_touching->getNorm();
		return std::experimental::optional<IntersectData>(_intersectData);
	}

	return std::experimental::nullopt;
}

}
