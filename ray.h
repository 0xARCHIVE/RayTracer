#ifndef RAY_H
#define RAY_H

#include "vec3d.h"
#include "colordata.h"

namespace RayTracer {

class Ray {
	private:
		ColorData colorData;
	public:
		Ray(Vec3D position, Vec3D direction, int max_recursion_depth, ColorData c);
		Vec3D computeResult();
};

}

#endif
