#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include "colordata.h"

namespace RayTracer {

class Surface;
class Vec3;

struct IntersectData {
	const Surface * surface;
	ColorData colorData;
	Vec3 hitPos;
	Vec3 hitNorm;
	double hitDist;
};

}

#endif
