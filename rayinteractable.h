#ifndef RAYINTERACTABLE_H
#define RAYINTERACTABLE_H

#include "intersectdata.h"
#include "ray.h"

namespace RayTracer {

class RayInteractable {
	protected:
		bool canIntersectRays = false;
		bool canGenerateRays = false;
	public:
		RayInteractable();
		RayInteractable(bool _canIntersectRays, bool _canGenerateRays);
		virtual IntersectData intersect(const Ray& _r) = 0;
		bool canIntersectRays();
		bool canGenerateRays();
		void setIntersectRays(bool _canIntersectRays);
		void setGenerateRays(bool _canGenerateRays);
};

}

#endif
