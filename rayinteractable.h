#ifndef RAYINTERACTABLE_H
#define RAYINTERACTABLE_H

#include "intersectdata.h"
#include "ray.h"

namespace RayTracer {

class RayInteractable {
	private:
		bool flag_canIntersectRays;
		bool flag_canGenerateRays;
	public:
		virtual IntersectData intersect(const Ray& r) = 0;
		bool canIntersectRays();
		bool canGenerateRays();
		void setIntersectRays(bool flag);
		void setGenerateRays(bool flag);
};

}

#endif
