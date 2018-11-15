#ifndef ENTITY_H
#define ENTITY_H

#include "scene.h"
#include "vec3.h"

namespace RayTracer {

class Entity {
	Scene& scene;
	Vec3 position;
	Vec3 angle;
};

}

#endif
