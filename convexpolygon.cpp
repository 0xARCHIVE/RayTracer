#include "convexpolygon.h"
#include "plane.h"
#include "ray.h"
#include "consts.h"

namespace RayTracer {

ConvexPolygon::ConvexPolygon(const Vec3 &worldPos, const Vec3 &worldAng) : Surface(worldPos, worldAng) {
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

std::unique_ptr<IntersectData> ConvexPolygon::intersectRay(const Ray &r) const {
	// hitPos must be "inside" all of the planes of the shape, can't just use the normal KDtree to find intersection
	bool found = false;
	double dist = 0;
	std::shared_ptr<Plane> plane_touching = nullptr;
	Vec3 point_touching;
	std::unique_ptr<IntersectData> intersectData;

	for (auto plane : this->getPlanes()) {
		std::unique_ptr<IntersectData> data = plane->intersectRay(r);
		if (data == nullptr) { continue; }

		Vec3 point = data->hitPos;
		if (!isInsideShape(point)) { continue; }

		Vec3 dV = (point - r.getPos());
		double dot = dV.dot(r.getDirection());
		if (dot < 0) { continue; }

		double _dist = dV.length();

		if (found == false || dist > (_dist + GLOBAL_SETTING_RAY_PRECISION)) {
			found = true;
			plane_touching = plane;
			point_touching = point;
			dist = _dist;
			intersectData = std::move(data);
		}
	}

	if (found) { return intersectData; }
	return nullptr;
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
