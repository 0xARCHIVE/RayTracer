#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include "vec3.h"

#include <vector>

namespace RayTracer {

struct ImageData {
	int resolution_x;
	int resolution_y;
	std::vector<Vec3> RGBvalues;
};

}

#endif
