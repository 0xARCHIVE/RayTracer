#ifndef COLORDATA_H
#define COLORDATA_H

#include "vec3d.h"

namespace RayTracer {

struct ColorData {
	Vec3D color;
	float emissivity;
	float multiplier;
};

}

#endif
