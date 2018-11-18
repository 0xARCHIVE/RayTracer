#ifndef ENTITY_H
#define ENTITY_H

#include "vec3.h"

#include <vector>

namespace RayTracer {

class Scene;
class Entity {
	protected:
		Entity* parent;
		std::vector<Entity*> children;
		Scene* scene;
		Vec3 position;
		Vec3 angle;

		Vec3 localX;
		Vec3 localY;
		Vec3 localZ;

		void translateChildrenTo(const Vec3& _vector);
		void rotateChildrenTo(const Vec3& _angle);
	public:
		Entity(Scene * const _scene, const Vec3& _position, const Vec3& _angle);
		virtual void setScene(Scene * const _scene);
		Scene * getScene() const;

		void setPosition(const Vec3& _position);
		void setAngle(const Vec3& _angle);
		Vec3 getPosition() const;
		Vec3 getAngle() const;
		void translate(const Vec3& _vector);
		void rotate(const Vec3& _angle);

		bool hasParent();
		Entity * getParent();
		bool hasChildren();
		std::vector<Entity*> getChildren();
		void addChild(Entity * const _child, bool dontCallAgain = false);
		void setParent(Entity * const _parent, bool dontCallAgain = false);

		Vec3 up() const;
		Vec3 forward() const;
		Vec3 right() const;
};

}

#endif
