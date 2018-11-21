#ifndef COLORDATA_H
#define COLORDATA_H

#include "vec3.h"

namespace RayTracer {

struct ColorData {
	Vec3 color = Vec3(0,0,0);
	double emissivity = 0;
	double reflectivity = 0;
	double transmissivity = 0;
	double multiplier = 0;
};

}

#endif
