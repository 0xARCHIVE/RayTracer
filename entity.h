#ifndef ENTITY_H
#define ENTITY_H

namespace RayTracer {

class Entity {
	private:
		std::shared_ptr<const Scene> scene;

		std::shared_ptr<Entity> parent;
		std::vector<std::shared_ptr<Entity>> children;
		KDNode kdnode;

		Vec3 worldPos;
		Vec3 localPos;
		Quat worldQuat;
		Quat localQuat;

		BoundingBox aabb;
		bool canIntersectRays = false;
		bool canGenerateRays = false;

		void recalculateKDtree();

		void recalculateAABB();
		void setAABB(const BoundingBox &aabb);

	public:
		Entity(shared_ptr<const Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng);
		virtual ~Entity();

		void setScene(std::shared_ptr<const Scene> scene);
		std::shared_ptr<const Scene> getScene() const;

		void setPos(const Vec3 &worldPos);
		void setAng(const Vec3 &worldAng);

		void translate(const Vec3 &dV);
		void translateChildren(const Vec3 &dV);
		void translateChildrenTo(const Vec3 &worldPos);

		void rotate(const Vec3 &dA);
		void rotateChildren(const Vec3 &dA);
		void rotateChildrenTo(const Vec3 &worldAng);

		void childrenSnapToParent();
		void snapToParent();

		Vec3 getPos() const;
		Vec3 getAng() const;
		Vec3 getMidPoint() const;

		Vec3 up() const;
		Vec3 forward() const;
		Vec3 right() const;

		Vec3 toWorld(const Vec3 &v) const;
		Vec3 toWorldOrientation(const Vec3 &v) const;
		Quat toWorldOrientation(const Quat &q) const;

		Vec3 toLocal(const Vec3 &v) const;
		Vec3 toLocalOrientation(const Vec3 &v) const;
		Quat toLocalOrientation(const Quat &q) const;

		bool hasParent() const;
		bool hasChildren() const;
		std::shared_ptr<Entity> getParent() const;
		std::vector<std::shared_ptr<Entity>> getChildren() const;
		void setParent(std::shared_ptr<Entity> parent, bool dontCallAgain = false);
		void addChild(std::shared_ptr<Entity> child, bool dontCallAgain = false);

		virtual std::experimental::optional<IntersectData> intersectRay(const Ray &r) const;
		bool canIntersectRays() const;
		bool canGenerateRays() const;

		virtual std::vector<Vec3> getCorners() const;
		void setCorners(const Vec3 &v1, const Vec3 &v2) const;
		const BoundingBox& getAABB() const;
		bool hasAABB() const;
};

}

#endif
