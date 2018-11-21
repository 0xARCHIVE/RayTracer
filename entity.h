#ifndef ENTITY_H
#define ENTITY_H

#include "vec3.h"
#include "quat.h"

#include <vector>

namespace RayTracer {

class Scene;

class Entity {
	protected:
		Entity* parent;
		std::vector<Entity*> children;
		Scene* scene;

		Vec3 worldPosition;
		Vec3 localPosition;

		Quat worldQuat;
		Quat localQuat;
	public:
		Entity(Scene * const _scene, const Vec3& _position, const Vec3& _angle);
		void setScene(Scene * const _scene);
		Scene * getScene() const;

		void setPosition(const Vec3& _position);
		void setAngle(const Vec3& _angle);
		Vec3 getPosition() const;
		Vec3 getAngle() const;
		void translate(const Vec3& _vector);
		void rotate(const Vec3& _angle);

		Vec3 toWorld(const Vec3 &v) const;
		Quat toWorldOrientation(const Quat &q) const;
		Vec3 toWorldOrientation(const Vec3 &v) const;

		Vec3 toLocal(const Vec3 &v) const;
		Quat toLocalOrientation(const Quat &q) const;
		Vec3 toLocalOrientation(const Vec3 &v) const;

		bool hasParent() const;
		Entity * getParent() const;
		bool hasChildren() const;
		std::vector<Entity*> getChildren();
		void addChild(Entity * const _child, bool dontCallAgain = false);
		void setParent(Entity * const _parent, bool dontCallAgain = false);

		void translateChildrenTo(const Vec3& _vector);
		void translateChildren(const Vec3& _vector);
		void rotateChildrenTo(const Vec3& _angle);
		void rotateChildren(const Vec3& _angle);

		void childrenSnapToParent();
		void snapToParent();

		Vec3 up() const;
		Vec3 forward() const;
		Vec3 right() const;
};

}

#endif
