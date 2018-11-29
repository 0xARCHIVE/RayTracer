#include "kdnode.h"
#include "ray.h"
#include "consts.h"

namespace RayTracer {

// https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/

KDNode::KDNode() {
	this->setEnts(std::vector<std::shared_ptr<Entity>>());
	this->build(this->getEnts());
}

KDNode::~KDNode() {}

bool KDNode::hasLeft() const {
	return (this->getLeft() != nullptr);
}

bool KDNode::hasRight() const {
	return (this->getRight() != nullptr);
}

std::shared_ptr<KDNode> KDNode::getLeft() const {
	return this->left;
}

std::shared_ptr<KDNode> KDNode::getRight() const {
	return this->right;
}

void KDNode::setLeft(std::shared_ptr<KDNode> left) {
	this->left = left;
}

void KDNode::setRight(std::shared_ptr<KDNode> right) {
	this->right = right;
}

const std::vector<std::shared_ptr<Entity>> KDNode::getEnts() const {
	return this->ents;
}

void KDNode::setEnts(const std::vector<std::shared_ptr<Entity>> ents) {
	this->ents = ents;
	this->recalculateAABB();
}

const BoundingBox& KDNode::getAABB() const {
	return this->aabb;
}

BoundingBox& KDNode::getAABB() {
	return this->aabb;
}

void KDNode::build(const std::vector<std::shared_ptr<Entity>> ents) {
	this->setEnts(ents);

	if (ents.size() == 0) { return; }
	if (ents.size() == 1) {
		this->setLeft(std::make_shared<KDNode>());
		this->setRight(std::make_shared<KDNode>());
		return;
	}

	Vec3 midpoint(0,0,0);
	for (auto ent : ents) {
		midpoint += ent->getMidPoint();
	}
	midpoint*=(1.0/ents.size());

	std::vector<std::shared_ptr<Entity>> leftEnts;
	std::vector<std::shared_ptr<Entity>> rightEnts;
	int axis = this->getAABB().getLongestAxis();
	for (auto ent : ents) {
		switch(axis) {
			case 0:	// x
				midpoint.getX() >= ent->getMidPoint().getX() ? rightEnts.push_back(ent) : leftEnts.push_back(ent);
				break;

			case 1:	// y
				midpoint.getY() >= ent->getMidPoint().getY() ? rightEnts.push_back(ent) : leftEnts.push_back(ent);
				break;

			case 2:	// z
				midpoint.getZ() >= ent->getMidPoint().getZ() ? rightEnts.push_back(ent) : leftEnts.push_back(ent);
				break;
		}
	}

	if (leftEnts.size() == 0 && rightEnts.size() > 0) { leftEnts = rightEnts; }
	if (rightEnts.size() == 0 && leftEnts.size() > 0) { rightEnts = leftEnts; }

	int matches = 0;
	for (auto ent_left : leftEnts) {
		for (auto ent_right : rightEnts) {
			if (ent_left == ent_right) { matches++; }
		}
	}

	std::shared_ptr<KDNode> nodeL = std::make_shared<KDNode>();
	std::shared_ptr<KDNode> nodeR = std::make_shared<KDNode>();
	if ((double)matches/leftEnts.size() < 0.5 && (double)matches/rightEnts.size() < 0.5) {
		nodeL->build(leftEnts);
		nodeR->build(rightEnts);
	}
	this->setLeft(nodeL);
	this->setRight(nodeR);

	return;
}

std::unique_ptr<IntersectData> KDNode::intersectRay(const Ray &r) const {
	std::unique_ptr<IntersectData> aabbIntersect = this->getAABB().intersectRay(r);
	if (aabbIntersect == nullptr) { return nullptr; }

	bool hit_ent = false;
	double minDist = 0;

	std::unique_ptr<IntersectData> intersectData;

	if (!this->hasLeft() || !this->hasRight()) { return nullptr; }
	if (this->getLeft()->getEnts().size() > 0 || this->getRight()->getEnts().size() > 0) {
		std::unique_ptr<IntersectData> hitLeft = this->getLeft()->intersectRay(r);
		std::unique_ptr<IntersectData> hitRight = this->getRight()->intersectRay(r);

		if (hitLeft && !hitRight) { return hitLeft; }
		if (!hitLeft && hitRight) { return hitRight; }
		if (!hitLeft && !hitRight) { return nullptr; }

		double distLeft = hitLeft->hitDist;
		double distRight = hitRight->hitDist;

		if (distLeft < distRight) { return hitLeft; } else { return hitRight; }

		return nullptr;
	} else {
		for (auto ent : this->getEnts()) {
			if (ent == nullptr) { continue;}
			if (!ent->canIntersectRays()) { continue; }
			if (!ent->getAABB().intersectRay(r)) { continue; }

			std::unique_ptr<IntersectData> ent_intersectData = ent->intersectRay(r);
			if (!ent_intersectData) { continue; }

			Vec3 dV = ent_intersectData->hitPos - r.getPos();

			double dot = dV.dot(r.getDirection());
			if (dot < 0) { continue; }

			double dist = dV.length();

			if (!hit_ent || minDist > (dist + GLOBAL_SETTING_RAY_PRECISION)) {
				hit_ent = true;
				minDist = dist;
				intersectData = std::move(ent_intersectData);
			}
		}

		if (hit_ent) { return intersectData; }
		return nullptr;
	}

	return nullptr;
}

void KDNode::setAABB(const BoundingBox &aabb) {
	this->aabb.copy(aabb);
}

void KDNode::recalculateAABB() {
	this->getAABB().expandToInclude(this->getEnts());
}

}

