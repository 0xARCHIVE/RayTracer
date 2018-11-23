#include "boundableentity.h"
#include "vec3.h"
#include "boundingbox.h"
#include "ray.h"
#include "surface.h"

namespace RayTracer {

BoundableEntity::BoundableEntity(Scene * const _scene, const Vec3& _position, const Vec3& _angle) : Entity(_scene, _position, _angle) {
	refreshBoundingBox();
}

BoundableEntity::~BoundableEntity() {
	if (getBoundingBox() != nullptr) { delete boundingBox; }
}

void BoundableEntity::setAngle(const Vec3& _angle) {
	refreshBoundingBox();
	return Entity::setAngle(_angle);
}

void BoundableEntity::setPosition(const Vec3& _position) {
	return Entity::setPosition(_position);
}

void BoundableEntity::addChild(Surface * const _surface) {
	refreshBoundingBox();
	return Entity::addChild(_surface);
}

void BoundableEntity::refreshBoundingBox() {
	std::vector<Vec3> coords = getMaxCoords();
	if (coords.size() != 2 || (coords[0] == Vec3(0,0,0) && coords[1] == Vec3(0,0,0))) {
		delete boundingBox;
		boundingBox = nullptr;
		return;
	}

	Vec3 v1 = coords[0];
	Vec3 v2 = coords[1];

	Vec3 cornerToCorner = v2 - v1;
	Vec3 position = cornerToCorner*0.5 + getPosition();
	Vec3 dimensions = cornerToCorner.abs();

	boundingBox = new BoundingBox(getScene(), position, dimensions);
}

BoundingBox * BoundableEntity::getBoundingBox() {
	return boundingBox;
}

bool BoundableEntity::hasBoundingBox() const {
	return (boundingBox == nullptr);
}

bool BoundableEntity::doesRayHit(const Ray& r) const {
	// todo
	return false;
}

}
