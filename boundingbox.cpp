#include "boundingbox.h"
#include "ray.h"
#include "vec3.h"
#include "intersectdata.h"

namespace RayTracer {

BoundingBox::BoundingBox(Scene * const _scene, const Vec3& _position, const Vec3& _dimensions) : Entity(_scene, _position, Vec3(0,0,0)), RayInteractable(true, false) {
	setDimensions(_dimensions);
}

BoundingBox::~BoundingBox() {}

Vec3 BoundingBox::getDimensions() const {
	return dimensions;
}

void BoundingBox::setDimensions(const Vec3& _dimensions) {
	dimensions = _dimensions;
}

bool BoundingBox::testIntersection(const Ray& r, bool testForwards, bool testBackwards) {
	if (intersect(r,testForwards,testBackwards)) { return true; }
	return false;
}

std::experimental::optional<IntersectData> BoundingBox::intersect(const Ray& r, bool testForwards, bool testBackwards) {
	// todo: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
	return std::experimental::nullopt;
}

}
