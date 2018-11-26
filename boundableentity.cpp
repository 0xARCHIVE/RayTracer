#include "boundableentity.h"
#include "vec3.h"
#include "boundingbox.h"
#include "ray.h"
#include "surface.h"

#include <cmath>
#include <iostream>

namespace RayTracer {

BoundableEntity::BoundableEntity(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : RayInteractable(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	boundingBox = new BoundingBox(_scene,_position,Vec3(0,0,0));
}

BoundableEntity::~BoundableEntity() {
	std::cout << "bb entity destructor " << getBoundingBox() << std::endl;
	if (hasBoundingBox()) {
		delete boundingBox;
		boundingBox = nullptr;
	}
	std::cout << "kek" << std::endl;
}

void BoundableEntity::enableAABB() {
	enabled = true;

	for (auto child : getChildren()) {
		static_cast<BoundableEntity *>(child)->enableAABB();
	}
	refreshBoundingBox();
}

void BoundableEntity::setAngle(const Vec3& _angle) {
	refreshBoundingBox();
	return RayInteractable::setAngle(_angle);
}

void BoundableEntity::setPosition(const Vec3& _position) {
	return RayInteractable::setPosition(_position);
}

void BoundableEntity::addChild(Surface * const _surface) {
	refreshBoundingBox();
	return RayInteractable::addChild(_surface);
}

std::vector<Vec3> BoundableEntity::getMaxCoords() const {
	return std::vector<Vec3>{Vec3(0,0,0),Vec3(0,0,0)};
}

void BoundableEntity::refreshBoundingBox() {
	if (!enabled) { return; }
	std::vector<Vec3> coords = getMaxCoords();
	if (coords.size() != 2 || coords[0] == coords[1]) {
		if (hasBoundingBox()) {
			delete boundingBox;
			boundingBox = nullptr;
		}
		return;
	}

	Vec3 v1 = coords[0];
	Vec3 v2 = coords[1];

	Vec3 minV( std::min(v1.getX(),v2.getX()), std::min(v1.getY(),v2.getY()), std::min(v1.getZ(),v2.getZ()));
	Vec3 maxV( std::max(v1.getX(),v2.getX()), std::max(v1.getY(),v2.getY()), std::max(v1.getZ(),v2.getZ()));

	Vec3 cornerToCorner = v2 - v1;
	Vec3 position = (minV+maxV)*0.5;
	Vec3 dimensions = cornerToCorner.abs();

	setBoundingBox(new BoundingBox(getScene(), position, dimensions));
}

void BoundableEntity::setBoundingBox(BoundingBox * bb) {
	if (hasBoundingBox()) { delete boundingBox; }
	if (bb == nullptr) { boundingBox = new BoundingBox(getScene(), Vec3(0,0,0), Vec3(0,0,0)); }
	boundingBox = bb;
	enabled = true;
}

BoundingBox * BoundableEntity::getBoundingBox() const {
	return boundingBox;
}

bool BoundableEntity::hasBoundingBox() const {
	return (boundingBox != nullptr);
}

bool BoundableEntity::doesRayHitBB(const Ray& r, bool testForwards, bool testBackwards) const {
	if (!hasBoundingBox()) { return false; }
	return (boundingBox->testIntersection(r,testForwards,testBackwards));
}

}
