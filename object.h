#ifndef OBJECT_H
#define OBJECT_H

#include "vec3d.h"
#include "boundingbox.h"
#include "surface.h"
#include "intersectdata.h"

namespace RayTracer {

class Object {
	private:
		Vec3D position;
		Vec3D orientation;
		Surface * surface;
		BoundingBox bounding_box;
	public:
		bool checkRayIntersectBB(Ray * r);
		IntersectData getIntersectData(Ray * r);
};

}

#endif
