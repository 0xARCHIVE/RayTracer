#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include "surface.h"
#include "colordata.h"
#include "vec3.h"

namespace RayTracer {

struct IntersectData {
	Surface& surface;
	ColorData& colorData;
	Vec3 hitPos;
	Vec3 surfaceNorm;
};

}

#endif
