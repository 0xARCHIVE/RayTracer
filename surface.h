#ifndef SURFACE_H
#define SURFACE_H

#include "ray.h"
#include "vec3d.h"
#include "colordata.h"
#include "raygenerator.h"

namespace RayTracer {

class Surface : public RayGenerator {
	private:
		Vec3D position;
		Vec3D angle;
	public:
		virtual Vec3D getIntersectPoint(Ray * r) = 0;
		virtual Vec3D getNormal(Vec3D position) = 0;
		virtual ColorData getColorData(Vec3D position) = 0;
};

}

#endif
