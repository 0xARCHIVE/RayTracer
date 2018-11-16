#ifndef ENTITY_H
#define ENTITY_H

#include "scene.h"
#include "vec3.h"

namespace RayTracer {

class Entity {
	protected:
		Scene& scene;
		Vec3 position;
		Vec3 angle;
	public:
		Entity(const Scene& _scene, const Vec3& _position, const Vec3& _angle);
		void setScene(const Scene& _scene);
		void setPosition(const Vec3& _position);
		void setAngle(const Vec3& _angle);
		Scene& getScene();
		Vec3 getPosition();
		Vec3 getAngle();
};

}

#endif
