#include "entity.h"
#include "scene.h"
#include "ray.h"
#include "intersectdata.h"
#include "kdnode.h"

namespace RayTracer {

Entity::Entity(const Vec3 &worldPos, const Vec3 &worldAng) {
	this->scene = nullptr;
	this->parent = nullptr;

	this->setPos(worldPos);
	this->setAng(worldAng);
}

Entity::~Entity() {}

void Entity::setScene(Scene * scene) {
	this->scene = scene;

	for (auto child : this->getChildren()) {
		child->setScene(scene);
	}
}

Scene * Entity::getScene() const {
	return this->scene;
}

void Entity::setPos(const Vec3 &worldPos) {
	this->worldPos = worldPos;
	this->localPos = Vec3(0,0,0);

	if (this->hasParent()) {
		this->localPos = this->getParent()->toLocal(this->getPos());
	}

	this->recalculateKDtree();
}

void Entity::setAng(const Vec3 &worldAng) {
	Quat q(worldAng);
	this->worldQuat = q;
	this->localQuat = Quat(Vec3(0,0,0));

	if (this->hasParent()) {
		this->localQuat = this->getParent()->toLocalOrientation(q);
	}

	this->recalculateKDtree();
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

/*Vec3 Entity::getPos() const {
	return this->worldPos;
}

Vec3 Entity::getAng() const {
	return this->worldQuat.toAngle();
}*/

Vec3 Entity::getMidPoint() const {
	if (!this->hasChildren()) { return this->getPos(); }

	Vec3 midPoint(0,0,0);
	for (auto child : this->getChildren()) {
		midPoint += child->getPos();
	}

	return midPoint*(1.0/this->getChildren().size());
}

/*Vec3 Entity::up() const {
	return this->toWorldOrientation(Vec3(0,0,1));
}

Vec3 Entity::forward() const {
	return this->toWorldOrientation(Vec3(1,0,0));
}

Vec3 Entity::right() const {
	return this->toWorldOrientation(Vec3(0,1,0));
}*/

Vec3 Entity::toWorld(const Vec3 &v) const {
	return this->toWorldOrientation(v) + this->getPos();
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

Entity * Entity::getParent() const {
	return this->parent;
}

std::vector<std::shared_ptr<Entity>> Entity::getChildren() const {
	return this->children;
}

void Entity::setParent(Entity * parent) {
	if (this->hasParent()) { return; }
	if (parent == nullptr) { return; }

	this->parent = parent;

	this->localQuat = parent->toLocalOrientation(this->worldQuat);
	this->localPos = this->getParent()->toLocal(this->getPos());
}

void Entity::addChild(std::shared_ptr<Entity> child) {
	if (child == nullptr) { return; }
	if (child->hasParent()) { return; }

	this->children.push_back(child);

	child->setParent(this);

	this->recalculateKDtree();
}

std::experimental::optional<IntersectData> Entity::intersectRay(const Ray &r) const {
	return this->kdnode->intersectRay(r);
}

/*bool Entity::canIntersectRays() const {
	return this->fl_canIntersectRays;
}

bool Entity::canGenerateRays() const {
	return this->fl_canGenerateRays;
}

bool Entity::isVisibile() const {
	return (this->canIntersectRays() && this->canGenerateRays());
}*/

void Entity::setIntersectRays(bool b) {
	this->fl_canIntersectRays = b;
}

void Entity::setGenerateRays(bool b) {
	this->fl_canGenerateRays = b;
}

void Entity::setVisible(bool b) {
	this->setIntersectRays(b);
	this->setGenerateRays(b);
}

std::vector<Vec3> Entity::getCorners() const {
	return this->getAABB().getCorners();
}

void Entity::setCorners(const Vec3 &v1, const Vec3 &v2) {
	return this->getAABB().setCorners(v1,v2);
}

const BoundingBox& Entity::getAABB() const {
	return this->aabb;
}

BoundingBox& Entity::getAABB() {
	return this->aabb;
}

void Entity::recalculateKDtree() {
	if (this->kdnode == nullptr) { this->kdnode = std::make_shared<KDNode>(); }
	this->recalculateAABB();

	for (auto child : this->getChildren()) {
		child->recalculateKDtree();
	}

	this->kdnode->build(this->getChildren());

	if (this->getScene() == nullptr) { return; }
	this->getScene()->recalculateKDtree();
}

void Entity::recalculateAABB() {
	for (auto child : this->getChildren()) {
		child->recalculateAABB();
	}

	std::vector<Vec3> corners = this->getCorners();
	Vec3 v1 = corners[0];
	Vec3 v2 = corners[1];

	this->setAABB(BoundingBox());
	this->getAABB().expandToInclude(v1,v2);
	this->getAABB().expandToInclude(this->getChildren());
}

void Entity::setAABB(const BoundingBox &aabb) {
	this->getAABB().copy(aabb);
}

}
