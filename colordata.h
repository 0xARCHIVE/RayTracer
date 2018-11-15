#ifndef COLORDATA_H
#define COLORDATA_H

#include "vec3.h"

namespace RayTracer {

struct ColorData {
	Vec3 color;
	float emissivity;
	float multiplier;
};

}

#endif
