#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include "surface.h"
#include "colordata.h"
#include "vec3d.h"

namespace RayTracer {

struct IntersectData {
	Surface * surface;
	ColorData * colorData;
	Vec3D hitPos;
	Vec3D surfaceNorm;
};

}

#endif
