#include "file.h"
#include "vec3.h"
#include "imagedata.h"

#include <cmath>
#include <fstream>
#include <iostream>

namespace RayTracer {

File::File(const std::string& _filepath) {
	filepath = _filepath;
}

void File::writeImageData(const ImageData& _data) {
	std::cout << "writing to " << filepath << std::endl;

	std::ofstream file;
	file.open(filepath, std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		std::cerr << "Failed to open file " << filepath << std::endl;
	}

	file << "P3\n" << _data.resolution_x << " " << _data.resolution_y << " 255\n";

	for (auto rgb : _data.RGBvalues) {
		double r = rgb.getX()*255.0;
		double g = rgb.getY()*255.0;
		double b = rgb.getZ()*255.0;

		r = (r > 255) ? 255 : r;
		g = (g > 255) ? 255 : g;
		b = (b > 255) ? 255 : b;

		file << round(r) << " " << round(g) << " " << round(b) << "\n";
	}

	file.close();
}

}
