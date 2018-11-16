#ifndef ENTITY_H
#define ENTITY_H

#include "vec3.h"

namespace RayTracer {

class Scene;
class Entity {
	protected:
		Scene* scene;
		Vec3 position;
		Vec3 angle;
	public:
		Entity(Scene * const _scene, const Vec3& _position, const Vec3& _angle);
		virtual void setScene(Scene * const _scene);
		void setPosition(const Vec3& _position);
		void setAngle(const Vec3& _angle);
		Scene * getScene() const;
		Vec3 getPosition() const;
		Vec3 getAngle() const;
};

}

#endif
