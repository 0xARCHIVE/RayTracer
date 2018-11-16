#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"
#include "boundingbox.h"
#include "surface.h"
#include "vec3.h"

#include <vector>

namespace RayTracer {

class Object : public Entity {
	protected:
		BoundingBox boundingBox;
		std::vector<Surface> surfaces;
	public:
		Object(const Scene* _scene, const Vec3& _position, const Vec3& _angle, BoundingBox _boundingBox);
		void addSurface(Surface _surface);
		std::vector<Surface> getSurfaces();
		void setBoundingBox(BoundingBox _boundingBox);
		BoundingBox& getBoundingBox();
		virtual void setScene(const Scene* _scene);
};

}

#endif
