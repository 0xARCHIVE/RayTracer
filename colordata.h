#ifndef COLORDATA_H
#define COLORDATA_H

#include "vec3.h"

namespace RayTracer {

struct ColorData {
	Vec3 color = Vec3(0,0,0);
	float emissivity = 0;
	float multiplier = 0;
};

}

#endif
