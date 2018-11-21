#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include "colordata.h"
#include "vec3.h"

namespace RayTracer {

class Surface;

struct IntersectData {
	Surface* surface;
	ColorData colorData;
	Vec3 hitPos;
	Vec3 hitNorm;
};

}

#endif
