#ifndef IMAGEDATA_H
#define IMAGEDATA_H

namespace RayTracer {

struct ImageData {
	int resolution_x;
	int resolution_y;
	std::vector<Vec3> RGBvalues;

	ImageData() : resolution_x(), resolution_y() {}
};

}

#endif
