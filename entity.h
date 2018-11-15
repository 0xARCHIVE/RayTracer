#ifndef ENTITY_H
#define ENTITY_H

#include "scene.h"
#include "vec3.h"

namespace RayTracer {

class Entity {
	private:
		Scene& scene;
		Vec3 position;
		Vec3 angle;
	public:
		Entity(const Scene& scene, const Vec3& position, const Vec3& angle);
		void setScene(const Scene& scene);
		void setPosition(const Vec3& position);
		void setAngle(const Vec3& angle);
		Scene& getScene();
		Vec3 getPosition();
		Vec3 getAngle();
};

}

#endif
