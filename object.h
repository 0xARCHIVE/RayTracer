#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"
#include "boundingbox.h"
#include "surface.h"
#include "vec3.h"

#include <vector>

namespace RayTracer {

class Object : public Entity {
	private:
		BoundingBox boundingBox;
		std::vector<Surface> surfaces;
	public:
		Object(const Scene& scene, const Vec3& position, const Vec3& angle, BoundingBox boundingBox);
		void addSurface(Surface surface);
		std::vector<Surface> getSurfaces();
		void setBoundingBox(BoundingBox boundingBox);
		BoundingBox getBoundingBox();
};

}

#endif
