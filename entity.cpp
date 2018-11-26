#include "entity.h"
#include "scene.h"
#include "ray.h"
#include "intersectdata.h"
#include "kdnode.h"

namespace RayTracer {

Entity::Entity(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng) {
	this->parent = nullptr;

	this->setScene(scene);

	this->setPos(worldPos);
	this->setAng(worldAng);
}

Entity::~Entity() {}

void Entity::setScene(std::shared_ptr<Scene> scene) {
	this->scene = scene;

	for (auto child : this->getChildren()) {
		child->setScene(scene);
	}
}

std::shared_ptr<Scene> Entity::getScene() const {
	return this->scene;
}

void Entity::setPos(const Vec3 &worldPos) {
	this->worldPos = worldPos;
	this->localPos = Vec3(0,0,0);

	if (this->hasParent()) {
		this->localPos = this->getParent()->toLocal(this->getPos());
	}

	this->recalculateAABB();
	this->getScene()->recalculateKDtree();
}

void Entity::setAng(const Vec3 &worldAng) {
	Quat q(worldAng);
	this->worldQuat = q;
	this->localQuat = Quat(Vec3(0,0,0));

	if (this->hasParent()) {
		this->localQuat = this->getParent()->toLocalOrientation(q);
	}

	this->recalculateAABB();
	this->getScene()->recalculateKDtree();
}

void Entity::translate(const Vec3 &dV) {
	this->setPos(this->getPos() + dV);
	this->translateChildren(dV);
}

void Entity::translateChildren(const Vec3 &dV) {
	for (auto child : this->getChildren()) {
		child->translate(dV);
	}
}

void Entity::translateChildrenTo(const Vec3 &dV) {
	for (auto child : this->getChildren()) {
		child->setPos(dV);
	}
}

void Entity::rotate(const Vec3 &dA) {
	this->setAng(this->getAng() + dA);
	this->childrenSnapToParent();
}

void Entity::rotateChildren(const Vec3 &dA) {
	for (auto child : this->getChildren()) {
		child->rotate(dA);
	}
}

void Entity::rotateChildrenTo(const Vec3 &dA) {
	for (auto child : this->getChildren()) {
		child->setAng(dA);
	}
}

void Entity::snapToParent() {
	if (!this->hasParent()) { return; }
	this->worldPos = this->getParent()->toWorld(this->localPos);
	this->worldQuat = this->getParent()->toWorldOrientation(this->localQuat);
}

void Entity::childrenSnapToParent() {
	for (auto child : this->getChildren()) {
		child->snapToParent();
	}
}

Vec3 Entity::getPos() const {
	return this->worldPos;
}

Vec3 Entity::getAng() const {
	return this->worldQuat.toAngle();
}

Vec3 Entity::getMidPoint() const {
	if (!this->hasChildren()) { return this->getPos(); }

	Vec3 midPoint(0,0,0);
	for (auto child : this->getChildren()) {
		midPoint += child->getPos();
	}

	return midPoint*(1.0/this->getChildren().size());
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

Vec3 Entity::toWorld(const Vec3 &v) const {
	return toWorldOrientation(v) + this->getPos();
}

Vec3 Entity::toWorldOrientation(const Vec3 &v) const {
	return v.rotate(this->worldQuat);
}

Quat Entity::toWorldOrientation(const Quat &q) const {
	return (q*this->worldQuat);
}

Vec3 Entity::toLocal(const Vec3 &v) const {
	Vec3 dV = v - this->getPos();
	return this->toLocalOrientation(dV);
}

Vec3 Entity::toLocalOrientation(const Vec3 &v) const {
	return v.rotate(this->worldQuat.conjugate());
}

Quat Entity::toLocalOrientation(const Quat &q) const {
	return q*this->worldQuat.conjugate();
}

bool Entity::hasParent() const {
	return (nullptr != this->getParent());
}

bool Entity::hasChildren() const {
	return (children.size() > 0);
}

std::shared_ptr<Entity> Entity::getParent() const {
	return this->parent;
}

std::vector<std::shared_ptr<Entity>> Entity::getChildren() const {
	return this->children;
}

void Entity::setParent(std::shared_ptr<Entity> parent, bool dontCallAgain) {
	if (this->hasParent()) { return; }
	if (parent == nullptr) { return; }

	this->parent = parent;

	this->localQuat = parent->toLocalOrientation(this->worldQuat);
	this->localPos = this->getParent()->toLocal(this->getPos());

	// could cause issues: https://stackoverflow.com/questions/11711034/stdshared-ptr-of-this
	if (dontCallAgain) { return; }
//	parent->addChild(this,true);
	// TODO: FIX (weak ptr?)
}

void Entity::addChild(std::shared_ptr<Entity> child, bool dontCallAgain) {
	if (child == nullptr) { return; }
	if (child->hasParent()) { return; }

	this->children.push_back(child);
	this->recalculateAABB();

	if (!dontCallAgain) { return; }
//	child->setParent(this,true);
	// todo: fix
}

std::experimental::optional<IntersectData> Entity::intersectRay(const Ray &r) const {
	return this->kdnode->intersectRay(r);
}

bool Entity::canIntersectRays() const {
	return this->fl_canIntersectRays;
}

bool Entity::canGenerateRays() const {
	return this->fl_canGenerateRays;
}

void Entity::setIntersectRays(bool b) {
	this->fl_canIntersectRays = b;
}

void Entity::setGenerateRays(bool b) {
	this->fl_canGenerateRays = b;
}

std::vector<Vec3> Entity::getCorners() const {
	return this->getAABB().getCorners();
}

void Entity::setCorners(const Vec3 &v1, const Vec3 &v2) {
	return this->getAABB().setCorners(v1,v2);
}

const BoundingBox& Entity::getAABB() const {
	return (this->aabb);
}

BoundingBox& Entity::getAABB() {
	return (this->aabb);
}

void Entity::recalculateKDtree() {
	this->kdnode = kdnode->build(this->getChildren());
}

void Entity::recalculateAABB() {
	Vec3 AABBmin(0,0,0);
	Vec3 AABBmax(0,0,0);

	for (auto child : this->getChildren()) {
		child->recalculateAABB();

		std::vector<Vec3> corners = child->getCorners();
		Vec3 v1 = corners[0];
		Vec3 v2 = corners[0];

		AABBmin.setX( std::min( std::min(v1.getX(),v2.getX()), AABBmin.getX() ));
		AABBmin.setY( std::min( std::min(v1.getY(),v2.getY()), AABBmin.getY() ));
		AABBmin.setZ( std::min( std::min(v1.getZ(),v2.getZ()), AABBmin.getZ() ));

		AABBmax.setX( std::max( std::max(v1.getX(),v2.getX()), AABBmax.getX() ));
		AABBmax.setY( std::max( std::max(v1.getY(),v2.getY()), AABBmax.getY() ));
		AABBmax.setZ( std::max( std::max(v1.getZ(),v2.getZ()), AABBmax.getZ() ));
	}

	this->getAABB().setCorners(AABBmin,AABBmax);
}

void Entity::setAABB(const BoundingBox &aabb) {
	this->getAABB().copy(aabb);
}

}
