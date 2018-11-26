#include "convexpolygon.h"
#include "consts.h"
#include "ray.h"
#include "intersectdata.h"
#include "vec3.h"
#include "plane.h"

#include <algorithm>
#include <iostream>

namespace RayTracer {

ConvexPolygon::ConvexPolygon(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {}

ConvexPolygon::~ConvexPolygon() {}

std::experimental::optional<Vec3> ConvexPolygon::getIntersectionPoint(const Ray& _r, bool testForwards = true, bool testBackwards = false) {
	std::experimental::optional<IntersectData> _intersectDataOpt = getIntersectData(_r, testForwards, testBackwards);
	if (!_intersectDataOpt) { return std::experimental::nullopt; }
	return std::experimental::optional<Vec3>(_intersectDataOpt.value().hitPos);
}

std::experimental::optional<Vec3> ConvexPolygon::getHitNorm(const Vec3& _position) const {
	for (auto plane : getPlanes()) {
		if (plane->isPointInPlane(_position)) {
			return std::experimental::optional<Vec3>(plane->getNorm());
		}
	}
	return std::experimental::nullopt;
}

std::vector<Vec3> ConvexPolygon::getBasisVectors(double u, double v) const {
	return std::vector<Vec3>{Vec3(0,0,0)};
}

Vec3 ConvexPolygon::getPointOnSurface(double u, double v) {
	return Vec3(0,0,0);
}

void ConvexPolygon::addPlane(Plane * const _plane) {
	if (_plane == nullptr) { return; }
	planes.push_back(_plane);
	addChild(_plane);
}

std::vector<Plane *> ConvexPolygon::getPlanes() const {
	return planes;
}

bool ConvexPolygon::isPointInsideShape(const Vec3& _point) const {
	for (const auto plane : getPlanes()) {
		if (!plane->isPointInsidePlane(_point)) { return false; }
	}
	return true;
}

std::experimental::optional<IntersectData> ConvexPolygon::getIntersectData(const Ray& _r, bool testForwards = true, bool testBackwards = false) const {
	bool found = false;
	double dist;
	Plane * _plane_touching = nullptr;
	Vec3 _point_touching;
	IntersectData _data;

	for (auto plane : getPlanes()) {
		std::experimental::optional<IntersectData> _dataOpt = plane->getIntersectData(_r, testForwards, testBackwards);
		if (!_dataOpt) { continue; }
		Vec3 _point = _dataOpt.value().hitPos;

		if (!isPointInsideShape(_point)) { continue; }

		Vec3 dV = (_point - _r.getPosition());
		double _dot = dV.dot(_r.getDirection());

//		if (!testForwards && _dot > 0) { continue; }
//		if (!testBackwards && _dot < 0) { continue; }

		double _dist = dV.length();

		if (found == false || dist > (_dist + GLOBAL_SETTING_RAY_PRECISION)) {	// pick intersection closest to ray
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

std::experimental::optional<IntersectData> ConvexPolygon::getIntersectData(const Vec3& _point) const {
	// todo: find out why this function exists
	Ray r(getScene(), _point, Vec3(0,0,1), 1);
	return getIntersectData(r);
}

std::vector<Vec3> ConvexPolygon::getMaxCoords() const {
	// return two corners of BB enclosing convexpolygon
	bool set = false;
	double maxX = 0;
	double maxY = 0;
	double maxZ = 0;
	double minX = 0;
	double minY = 0;
	double minZ = 0;

	for (auto plane : getPlanes()) {
		std::vector<Vec3> coords = plane->getMaxCoords();
		Vec3 v1 = coords[0];
		Vec3 v2 = coords[1];

		Vec3 minV( std::min(v1.getX(),v2.getX()), std::min(v1.getY(),v2.getY()), std::min(v1.getZ(),v2.getZ())  );
		Vec3 maxV( std::max(v1.getX(),v2.getX()), std::max(v1.getY(),v2.getY()), std::max(v1.getZ(),v2.getZ())  );

		if (!set) {
			minX = minV.getX();
			minY = minV.getY();
			minZ = minV.getZ();

			maxX = maxV.getX();
			maxY = maxV.getY();
			maxZ = maxV.getZ();

			set = true;
			continue;
		}

		maxX = std::max(maxV.getX(), maxX);
		maxY = std::max(maxV.getY(), maxY);
		maxZ = std::max(maxV.getZ(), maxZ);

		minX = std::min(minV.getX(), minX);
		minY = std::min(minV.getY(), minY);
		minZ = std::min(minV.getZ(), minZ);
	}

	return std::vector<Vec3>{ Vec3(maxX,maxY,maxZ), Vec3(minX,minY,minZ) };
}

}
