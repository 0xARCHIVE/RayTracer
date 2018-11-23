#include "entity.h"

#include <experimental/optional>

namespace RayTracer {

Entity::Entity(Scene * const _scene, const Vec3& _position, const Vec3& _angle) {
	parent = nullptr;
	scene = nullptr;

	setPosition(_position);
	setAngle(_angle);
	setScene(_scene);
}

Entity::~Entity() {}

void Entity::setScene(Scene * const _scene) {
	scene = _scene;

	for (auto child : children) {
		child->setScene(_scene);
	}
}

void Entity::setPosition(const Vec3& _position) {
	worldPosition = _position;
	localPosition = Vec3(0,0,0);

	if (hasParent()) {
		localPosition = getParent()->toLocal(worldPosition);
	}
}

void Entity::setAngle(const Vec3& _angle) {
	Quat q(_angle);
	worldQuat = q;
	localQuat = Quat(Vec3(0,0,0));

	if (hasParent()) {
		localQuat = getParent()->toLocalOrientation(q);
	}
}

Scene* Entity::getScene() const {
	return scene;
}

Vec3 Entity::getPosition() const {
	return worldPosition;
}

Vec3 Entity::getAngle() const {
	return worldQuat.toAngle();
}

void Entity::translate(const Vec3& _vector) {
	setPosition(getPosition() + _vector);
	translateChildren(_vector);
}

void Entity::rotate(const Vec3& _angle) {
	setAngle(getAngle() + _angle);
	childrenSnapToParent();
}

void Entity::translateChildrenTo(const Vec3& _vector) {
	for (auto child : children) {
		child->setPosition(_vector);
	}
}

void Entity::translateChildren(const Vec3& _vector) {
	for (auto child : children) {
		child->translate(_vector);
	}
}

void Entity::rotateChildrenTo(const Vec3& _angle) {
	for (auto child : children) {
		child->setAngle(_angle);
	}
}

void Entity::rotateChildren(const Vec3& _angle) {
	for (auto child : children) {
		child->rotate(_angle);
	}
}

void Entity::childrenSnapToParent() {
	for (auto child : children) {
		child->snapToParent();
	}
}

void Entity::snapToParent() {
	// recalculate worldPos and worldQuat
	if (!hasParent()) { return; }
	worldPosition = getParent()->toWorld(localPosition);
	worldQuat = getParent()->toWorldOrientation(localQuat);
}

bool Entity::hasParent() const {
	if (nullptr == parent) { return false; }
	return true;
}

Entity* Entity::getParent() const {
	return parent;
}

bool Entity::hasChildren() const {
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

	localQuat = parent->toLocalOrientation(worldQuat);
	localPosition = getParent()->toLocal(worldPosition);

	if (dontCallAgain) { return; }	// prevents looping
	_parent->addChild(this, true);
}

Vec3 Entity::up() const {
	return toWorldOrientation(Vec3(0,0,1));
}

Vec3 Entity::forward() const {
	return toWorldOrientation(Vec3(1,0,0));
}

Vec3 Entity::right() const {
	return toWorldOrientation(Vec3(0,1,0));
}

Vec3 Entity::toWorld(const Vec3& _vector) const {
	// transforms _vector out of our vectorspace
	return toWorldOrientation(_vector) + worldPosition;
}

Vec3 Entity::toWorldOrientation(const Vec3& _vector) const {
	// transforms _vector out of our vectorspace without translating
	return _vector.rotate(worldQuat);
}

Quat Entity::toWorldOrientation(const Quat& _q) const {
	// transforms _q out of our vectorspace without translating
	return (_q*worldQuat);
}

Vec3 Entity::toLocal(const Vec3& _vector) const {
	// transforms _vector into our vectorspace
	Vec3 v = _vector - worldPosition;
	return toLocalOrientation(v);
}

Vec3 Entity::toLocalOrientation(const Vec3& _vector) const {
	// transforms _vector into our vectorspace without translating
	return _vector.rotate(worldQuat.conjugate());
}

Quat Entity::toLocalOrientation(const Quat& _q) const {
	// transforms _q into our vectorspace without translating
	// https://stackoverflow.com/a/22167097/4000963
	return _q*worldQuat.conjugate();
}

}
