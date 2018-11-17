#include "convexpolygon.h"

ConvexPolygon::ConvexPolygon(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {

}

std::experimental::optional<Vec3> ConvexPolygon::getIntersectionPoint(const Ray& _r) {
	// test all planes for "inside". If intersects one and insides all others, then we have an intersection with the surface
}

std::experimental::optional<Vec3> ConvexPolygon::getHitNorm(const Vec3& _position) {
	// if position is on the surface, then return intersected plane's hitNorm
}

std::vector<Vec3> ConvexPolygon::getBasisVectors(float u, float v) {
	return Vec3(0,0,0);
}

Vec3 ConvexPolygon::getPointOnSurface(float u, float v) {
	return Vec3(0,0,0);
}

std::experimental::optional<IntersectData> ConvexPolygon::intersect(const Ray& _r) {
	std::experimental::optional<Vec3> _intersection = getIntersectionPoint(_r);
	if (!_intersection) { return std::experimental::nullopt; }
	// todo: get and return intersectdata
}

void ConvexPolygon::addPlane(Plane * const _plane) {
	if (_plane == nullptr) { return; }
	planes.push_back(_plane);
}

std::vector<Plane *> ConvexPolygon::getPlanes() {
	return planes;
}

bool ConvexPolygon::isPointInsideShape(const Vec3& _point) {
	// check if point is "inside" every plane => if yes, then it's inside surface
}

