#ifndef KDNODE_H
#define KDNODE_H

#include "entity.h"
#include "boundingbox.h"

#include <memory>
#include <vector>
#include <experimental/optional>

namespace RayTracer {

class IntersectData;

class KDNode {
	private:
		std::vector<std::shared_ptr<Entity>> ents;

		std::shared_ptr<KDNode> left;
		std::shared_ptr<KDNode> right;

		BoundingBox aabb;

		void setAABB(const BoundingBox &aabb);
		void recalculateAABB();
	public:
		KDNode();
		~KDNode();

		bool hasLeft() const;
		bool hasRight() const;
		std::shared_ptr<KDNode> getLeft() const;
		std::shared_ptr<KDNode> getRight() const;
		void setLeft(std::shared_ptr<KDNode> left);
		void setRight(std::shared_ptr<KDNode> right);

		const std::vector<std::shared_ptr<Entity>> getEnts() const;
		void setEnts(const std::vector<std::shared_ptr<Entity>> ents);

		const BoundingBox& getAABB() const;
		BoundingBox& getAABB();

		void build(const std::vector<std::shared_ptr<Entity>> ents);
		std::unique_ptr<IntersectData> intersectRay(const Ray& _r) const;
};

}

#endif
