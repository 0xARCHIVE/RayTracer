#include "box.h"
#include "plane.h"

#include <iostream>
namespace RayTracer {

Box::Box(Scene* const _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions, bool _canIntersectRays, bool _canGenerateRays) : ConvexPolygon(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	dimensions = _dimensions;

	float depth = _dimensions.getX();
	float width = _dimensions.getY();
	float height = _dimensions.getZ();

	Plane * p1 = new Plane(_scene, _position + forward()*(depth/2), _angle + Vec3(-90,0,0), _canIntersectRays, _canGenerateRays);
	Plane * p2 = new Plane(_scene, _position - forward()*(depth/2), _angle + Vec3(90,0,0), _canIntersectRays, _canGenerateRays);
	Plane * p3 = new Plane(_scene, _position + right()*(width/2), _angle + Vec3(0,0,90), _canIntersectRays, _canGenerateRays);
	Plane * p4 = new Plane(_scene, _position - right()*(width/2), _angle + Vec3(0,0,-90), _canIntersectRays, _canGenerateRays);
	Plane * p5 = new Plane(_scene, _position + up()*(height/2), _angle, _canIntersectRays, _canGenerateRays);
	Plane * p6 = new Plane(_scene, _position - up()*(height/2), _angle + Vec3(0,0,180), _canIntersectRays, _canGenerateRays);

	addPlane(p1);
	addPlane(p2);
	addPlane(p3);
	addPlane(p4);
	addPlane(p5);
	addPlane(p6);

	planesToDelete.push_back(p1);
	planesToDelete.push_back(p2);
	planesToDelete.push_back(p3);
	planesToDelete.push_back(p4);
	planesToDelete.push_back(p5);
	planesToDelete.push_back(p6);
}

Box::~Box() {
	for (auto plane : planesToDelete) {
		delete plane;
	}
	planesToDelete.clear();
}

}
