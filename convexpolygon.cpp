#include "convexpolygon.h"
#include "plane.h"
#include "ray.h"
#include "consts.h"

namespace RayTracer {

ConvexPolygon::ConvexPolygon(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng) : Surface(scene, worldPos, worldAng) {
	this->planes = std::vector<std::shared_ptr<Plane>>();
}

ConvexPolygon::~ConvexPolygon() {}

Vec3 ConvexPolygon::getPointOnSurface(double u, double v) const {
	return Vec3(0,0,0);
}

std::experimental::optional<Vec3> ConvexPolygon::getNorm(const Vec3 &worldPos) const {
	for (auto plane : this->getPlanes()) {
		if (plane->isInPlane(worldPos)) {
			return std::experimental::optional<Vec3>(plane->getNorm(worldPos));
		}
	}
	return std::experimental::nullopt;
}

std::experimental::optional<IntersectData> ConvexPolygon::intersectRay(const Ray &r) const {
	// hitPos must be "inside" all of the planes of the shape, can't just use the normal KDtree to find intersection
	bool found = false;
	double dist;
	std::shared_ptr<Plane> plane_touching = nullptr;
	Vec3 point_touching;
	IntersectData data;

	for (auto plane : this->getPlanes()) {
		std::experimental::optional<IntersectData> dataOpt = plane->intersectRay(r);
		if (!dataOpt) { continue; }
		Vec3 point = dataOpt.value().hitPos;
		if (!isInsideShape(point)) { continue; }

		Vec3 dV = (point - r.getPos());
		double _dist = dV.length();

		if (found == false || dist > (_dist + GLOBAL_SETTING_RAY_PRECISION)) {
			found = true;
			plane_touching = plane;
			point_touching = point;
			data = dataOpt.value();
			dist = _dist;
		}
	}

	if (found) {
		return std::experimental::optional<IntersectData>(data);
	}

	return std::experimental::nullopt;
}

void ConvexPolygon::addPlane(std::shared_ptr<Plane> plane) {
	if (plane == nullptr) { return; }
	this->planes.push_back(plane);
	this->addChild(plane);
}

std::vector<std::shared_ptr<Plane>> ConvexPolygon::getPlanes() const {
	return this->planes;
}

bool ConvexPolygon::isInsideShape(const Vec3 &worldPos) const {
	for (const auto plane : this->getPlanes()) {
		if (!plane->isInsidePlane(worldPos)) { return false; }
	}
	return true;
}

}
