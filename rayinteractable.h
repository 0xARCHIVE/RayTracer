#ifndef RAYINTERACTABLE_H
#define RAYINTERACTABLE_H

#include "intersectdata.h"
#include "ray.h"

namespace RayTracer {

class RayIntersectable {
	private:
		bool canIntersectRays;
		bool canGenerateRays;
	public:
		virtual IntersectData intersect(Ray& r) = 0;
};

}

#endif
