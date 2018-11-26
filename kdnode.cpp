#include "kdnode.h"
#include "ray.h"
#include "consts.h"

namespace RayTracer {

// https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/

KDNode::KDNode() {
	this->left = nullptr;
	this->right = nullptr;

	this->ents = std::vector<std::shared_ptr<Entity>>();
}

KDNode::~KDNode() {}

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

const std::vector<std::shared_ptr<Entity>>& KDNode::getEnts() const {
	return this->ents;
}

void KDNode::setEnts(const std::vector<std::shared_ptr<Entity>>& ents) {
	this->ents = ents;
	this->recalculateAABB();
}

const BoundingBox& KDNode::getAABB() const {
	return this->aabb;
}

std::shared_ptr<KDNode> KDNode::build(const std::vector<std::shared_ptr<Entity>>& ents) {
	std::shared_ptr<KDNode> node = std::make_shared<KDNode>();
	node->setEnts(ents);

	if (ents.size() == 0) { return node; }

	if (ents.size() == 1) {
		node->setLeft(std::make_shared<KDNode>());
		node->setRight(std::make_shared<KDNode>());
		return node;
	}

	Vec3 midpoint(0,0,0);
	for (auto ent : ents) {
		midpoint += (1.0/ents.size())*ent->getMidPoint();
	}
	midpoint*=(1.0/ents.size());

	std::vector<std::shared_ptr<Entity>> leftEnts;
	std::vector<std::shared_ptr<Entity>> rightEnts;
	int axis = node->getAABB().getLongestAxis();
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

	if ((double)matches/leftEnts.size() < 0.5 && (double)matches/rightEnts.size() < 0.5) {
		node->setLeft(node->build(leftEnts));
		node->setRight(node->build(rightEnts));
	} else {
		node->setLeft(std::make_shared<KDNode>());
		node->setRight(std::make_shared<KDNode>());
	}

	return node;
}

std::experimental::optional<IntersectData> KDNode::intersectRay(const Ray &r) const {
	std::experimental::optional<IntersectData> aabbIntersect = this->getAABB().intersectRay(r);
	if (!aabbIntersect) { return aabbIntersect; }

	bool hit_ent = false;
	double minDist;

	std::experimental::optional<IntersectData> intersectData;

	if (this->getLeft()->getEnts().size() > 0 || this->getRight()->getEnts().size() > 0) {
		std::experimental::optional<IntersectData> hitLeft = this->getLeft()->intersectRay(r);
		if (hitLeft) { return hitLeft; }

		std::experimental::optional<IntersectData> hitRight = this->getRight()->intersectRay(r);
		if (hitRight) { return hitRight; }

		return std::experimental::nullopt;
	} else {
		for (auto ent : this->getEnts()) {
			if (ent == nullptr) { continue;}
			if (!ent->getAABB().intersectRay(r)) { continue; }

			std::experimental::optional<IntersectData> ent_intersectData = ent->intersectRay(r);
			if (!ent_intersectData) { continue; }

			Vec3 dV = ent_intersectData.value().hitPos - r.getPos();
			double dist = dV.length();

			if (!hit_ent || minDist > (dist + GLOBAL_SETTING_RAY_PRECISION)) {
				hit_ent = true;
				minDist = dist;
				intersectData = ent_intersectData;
			}
		}

		if (hit_ent) { return intersectData; }
		return std::experimental::nullopt;
	}
}

void KDNode::setAABB(const BoundingBox &aabb) {
	this->aabb.copy(aabb);
}

void KDNode::recalculateAABB() {
	this->aabb.expandToInclude(this->getEnts());
}

}

