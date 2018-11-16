#ifndef RAYINTERACTABLE_H
#define RAYINTERACTABLE_H

#include "intersectdata.h"
#include "ray.h"

#include <experimental/optional>

namespace RayTracer {

class RayInteractable {
	protected:
		bool flag_canIntersectRays = false;
		bool flag_canGenerateRays = false;
	public:
		RayInteractable();
		RayInteractable(bool _canIntersectRays, bool _canGenerateRays);
		virtual std::experimental::optional<IntersectData> intersect(const Ray& _r) = 0;
		bool canIntersectRays();
		bool canGenerateRays();
		void setIntersectRays(bool _canIntersectRays);
		void setGenerateRays(bool _canGenerateRays);
};

}

#endif
