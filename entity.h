#ifndef ENTITY_H
#define ENTITY_H

#include "vec3.h"

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

		void translateChildrenBy(const Vec3& _vector);
		void rotateChildrenBy(const Vec3& _angle);
	public:
		Entity(Scene * const _scene, const Vec3& _position, const Vec3& _angle);
		virtual void setScene(Scene * const _scene);
		void setPosition(const Vec3& _position);
		void setAngle(const Vec3& _angle);
		Scene * getScene() const;
		Vec3 getPosition() const;
		Vec3 getAngle() const;
		void rotate(const Vec3& _angle);

		bool hasParent();
		Entity* getParent();
		bool hasChildren();
		std::vector<Entity*> getChildren();
		void addChild(Entity * const _child);
		void addParent(Entity * const _parent);

		Vec3 up();
		Vec3 forward();
		Vec3 right();
};

}

#endif
