#include "kdnode.h"
#include "boundingbox.h"
#include "boundableentity.h"
#include "scene.h"
#include "intersectdata.h"
#include "consts.h"

#include <iostream>

namespace RayTracer {

// https://blog.frogslayer.com/kd-trees-for-faster-ray-tracing-with-triangles/

KDNode::KDNode(Scene * const _scene) : BoundableEntity(_scene, Vec3(0,0,0), Vec3(0,0,0)) {
	left = nullptr;
	right = nullptr;

	ents = std::vector<BoundableEntity *>();
}

KDNode::~KDNode() {
	if (left != nullptr) { delete left; left = nullptr; }
	if (right != nullptr) { delete right; right = nullptr; }
}

KDNode * KDNode::build(const std::vector<BoundableEntity *>& ents) {
	KDNode * node = new KDNode(getScene());
	node->ents = ents;

	if (ents.size() == 0) { return node; }

	if (ents.size() == 1) {
		node->setBoundingBox(ents[0]->getBoundingBox()->copy());
		node->left = new KDNode(getScene());
		node->right = new KDNode(getScene());

		return node;
	}

	node->setBoundingBox(ents[0]->getBoundingBox());
	for (auto ent : ents) {
		node->getBoundingBox()->expand(ent->getBoundingBox());
	}

	Vec3 midpoint(0,0,0);
	for (auto ent : ents) {
		midpoint += (1.0/ents.size())*ent->getMidpoint();
	}

	std::vector<BoundableEntity *> leftEnts;
	std::vector<BoundableEntity *> rightEnts;
	int axis = node->getBoundingBox()->longestAxis();
	for (auto ent : ents) {
		switch(axis) {
			case 0:	// x
				midpoint.getX() >= ent->getMidpoint().getX() ? rightEnts.push_back(ent) : leftEnts.push_back(ent);
				break;

			case 1:	// y
				midpoint.getY() >= ent->getMidpoint().getY() ? rightEnts.push_back(ent) : leftEnts.push_back(ent);
				break;

			case 2:	// z
				midpoint.getZ() >= ent->getMidpoint().getZ() ? rightEnts.push_back(ent) : leftEnts.push_back(ent);
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
		node->left = node->build(leftEnts);
		node->right = node->build(rightEnts);
	} else {
		delete node->left;
		delete node->right;

		node->left = new KDNode(getScene());
		node->right = new KDNode(getScene());
	}

	return node;
}

std::experimental::optional<IntersectData> KDNode::intersect(const Ray& _r, bool testForwards, bool testBackwards) const {
	std::experimental::optional<IntersectData> bbox_intersect_opt = getBoundingBox()->intersect(_r,testForwards,testBackwards);
	if (bbox_intersect_opt) {
		bool hit_ent = false;
		double minDist;

		std::experimental::optional<IntersectData> _intersectData;

		if (left->ents.size() > 0 || right->ents.size() > 0) {
			std::experimental::optional<IntersectData> hitLeft_opt = left->intersect(_r,testForwards,testBackwards);
			if (hitLeft_opt) { return hitLeft_opt; }

			std::experimental::optional<IntersectData> hitRight_opt = right->intersect(_r,testForwards,testBackwards);
			if (hitRight_opt) { return hitRight_opt; }

			return std::experimental::nullopt;
		} else {
			for (auto ent : ents) {
				if (ent == nullptr) { continue;}
				if (!ent->doesRayHitBB(_r)) { continue; }

				std::experimental::optional<IntersectData> ent_intersectData = ent->intersect(_r,testForwards,testBackwards);
				if (!ent_intersectData) { continue; }
				Vec3 dV = ent_intersectData.value().hitPos - _r.getPosition();
				double dist = dV.length();

				if (!hit_ent || minDist > (dist + GLOBAL_SETTING_RAY_PRECISION)) {
					hit_ent = true;
					minDist = dist;
					_intersectData = ent_intersectData;
				}
			}

			if (hit_ent) { return _intersectData; }
			return std::experimental::nullopt;
		}
	}

	return std::experimental::nullopt;
}

}

