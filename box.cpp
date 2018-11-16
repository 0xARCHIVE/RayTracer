#include "box.h"

Box::Box(const Scene* _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	dimensions = _dimensions;
}

Vec3 Box::getIntersectionPoint(const Ray& _r) {
	// TODO
}

Vec3 Box::getHitNormal(const Vec3& _position) {
	// TODO
}
