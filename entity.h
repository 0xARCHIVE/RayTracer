#ifndef ENTITY_H
#define ENTITY_H

#include "boundingbox.h"
#include "quat.h"
#include "vec3.h"

#include <memory>
#include <vector>
#include <experimental/optional>

namespace RayTracer {

class Scene;
class Ray;
class IntersectData;
class KDNode;

class Entity {
	private:
		Scene * scene;
		std::shared_ptr<KDNode> kdnode;

		Entity * parent;
		std::vector<std::shared_ptr<Entity>> children;

		Vec3 worldPos;
		Vec3 localPos;
		Quat worldQuat;
		Quat localQuat;

		BoundingBox aabb;
		bool fl_canIntersectRays = true;
		bool fl_canGenerateRays = true;

		void setAABB(const BoundingBox &aabb);
		void setCorners(const Vec3 &v1, const Vec3 &v2);

	public:
		Entity(const Vec3 &worldPos, const Vec3 &worldAng);
		virtual ~Entity();

		void setScene(Scene * scene);
		Scene * getScene() const;

		void setPos(const Vec3 &worldPos);
		void setAng(const Vec3 &worldAng);

		void translate(const Vec3 &dV);
		void translateChildren(const Vec3 &dV);
		void translateChildrenTo(const Vec3 &worldPos);

		void rotate(const Vec3 &dA);
		void rotateChildren(const Vec3 &dA);
		void rotateChildrenTo(const Vec3 &worldAng);

		void snapToParent();
		void childrenSnapToParent();

		Vec3 getPos() const;
		Vec3 getAng() const;
		virtual Vec3 getMidPoint() const;

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
		Entity * getParent() const;
		std::vector<std::shared_ptr<Entity>> getChildren() const;
		void setParent(Entity * parent);
		void addChild(std::shared_ptr<Entity> child);

		virtual std::experimental::optional<IntersectData> intersectRay(const Ray &r) const;
		bool canIntersectRays() const;
		bool canGenerateRays() const;
		bool isVisibile() const;
		void setIntersectRays(bool b);
		void setGenerateRays(bool b);
		void setVisible(bool b);

		virtual std::vector<Vec3> getCorners() const;
		const BoundingBox& getAABB() const;
		BoundingBox& getAABB();
		void recalculateAABB();
		void recalculateKDtree();

};

}

#endif
