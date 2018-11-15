#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "vec3d.h"
#include "ray.h"

BoundingBox {
	private:
		Vec3D position;
		Vec3D angle;
		float width;
		float height;
		float depth;
	public:
		BoundingBox(Vec3D position, Vec3D angle, float width, float height, float depth);
		bool checkRayIntersect(Ray * r);
};

#endif
