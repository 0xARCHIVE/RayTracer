#ifndef KDNODE_H
#define KDNODE_H

namespace RayTracer {

class KDNode {
	private:
		std::vector<std::shared_ptr<Entity>> ents;

		std::shared_ptr<KDNode> left;
		std::shared_ptr<KDNode> right;

		BoundingBox aabb;

		void recalculateAABB();
		void setAABB(const BoundingBox &aabb);
	public:
		KDNode();
		~KDNode();

		std::shared_ptr<KDNode> getLeft() const;
		std::shared_ptr<KDNode> getRight() const;
		void setLeft(std::shared_ptr<KDNode> left);
		void setRight(std::shared_ptr<KDNode> right);

		const std::vector<std::shared_ptr<Entity>>& getEnts() const;
		void setEnts(const std::vector<std::shared_ptr<Entity>>& ents);

		const BoundingBox& getAABB() const;
		bool hasAABB() const;

		std::shared_ptr<KDNode> build(const std::vector<std::shared_ptr<Entity>>& ents);
		std::experimental::optional<IntersectData> intersectRay(const Ray& _r) const;
};

}

#endif
