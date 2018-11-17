#include "entity.h"

namespace RayTracer {

Entity::Entity(Scene * const _scene, const Vec3& _position, const Vec3& _angle) {
	localX = Vec3(1,0,0);
	localY = Vec3(0,1,0);
	localZ = Vec3(0,0,1);

	setPosition(_position);
	setAngle(_angle);
	setScene(_scene);
}

void Entity::setScene(Scene * const _scene) {
	scene = _scene;
}

void Entity::setPosition(const Vec3& _position) {
	translateChildrenBy(_position - position);
	position = _position;
}

void Entity::setAngle(const Vec3& _angle) {
	Vec3 dA = (_angle - getAngle());

	rotateChildrenBy(dA);
	localX = localX.rotate(dA);
	localY = localY.rotate(dA);
	localZ = localZ.rotate(dA);

	angle = _angle;
}

Scene* Entity::getScene() const {
	return scene;
}

Vec3 Entity::getPosition() const {
	return position;
}

Vec3 Entity::getAngle() const {
	return angle;
}

void Entity::translate(const Vec3& _vector) {
	setPosition(getPosition() + _vector);
}

void Entity::rotate(const Vec3& _angle) {
	setAngle(getAngle() + _angle);
}

void Entity::translateChildrenBy(const Vec3& _vector) {
	for (auto child : children) {
		child->translate(_vector);
	}
}

void Entity::rotateChildrenBy(const Vec3& _angle) {
	for (auto child : children) {
		Vec3 dV = (child->getPosition() - getPosition());
		dV = dV.rotate(_angle);
		Vec3 newPos = dV + getPosition();

		child->setPosition(newPos);
		child->rotate(_angle);
	}
}

bool Entity::hasParent() {
	if (parent == nullptr) { return false; }
	return true;
}

Entity* Entity::getParent() {
	return parent;
}

bool Entity::hasChildren() {
	if (children.size() > 0) { return true; }
	return false;
}

std::vector<Entity*> Entity::getChildren() {
	return children;
}

void Entity::addChild(Entity * const _child, bool dontCallAgain) {
	if (_child == nullptr) { return; }
	if (_child->hasParent()) { return; }

	children.push_back(_child);

	if (dontCallAgain) { return; }	// prevents looping
	_child->setParent(this, true);
}

void Entity::setParent(Entity * const _parent, bool dontCallAgain) {
	if (hasParent()) { return; }
	if (_parent == nullptr) { return; }

	parent = _parent;

	if (dontCallAgain) { return; }	// prevents looping
	_parent->addChild(this, true);
}

Vec3 Entity::up() const {
	return localZ;
}

Vec3 Entity::forward() const {
	return localX;
}

Vec3 Entity::right() const {
	return localY;
}

}
