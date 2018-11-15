#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include "surface.h"
#include "raygenerator.h"

namespace RayTracer {

class CameraSensor : public RayGenerator {
	private:
		Surface surface;
		int resolution_x;
		int resolution_y;
		float sensor_width;
		float sensor_height;
	public:
		CameraSensor(const Scene& scene, const Vec3& position, const Vec3& angle, const Surface& surface, int resolution_x, int resolution_y, float sensor_width, float sensor_height);
		Vec3 getPixelPosition(int x, int y);	// returns world position of pixel (x,y) on the sensor
		Vec3 captureImageData(int x, int y);	// returns (R,G,B) capture result from pixel (x,y)
};

}

#endif
