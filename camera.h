#ifndef CAMERA_H
#define CAMERA_H

#include "vec3d.h"
#include "camerasensor.h"

namespace RayTracer {

class Camera {
	private:
		Vec3D position;
		Vec3D angle;

		int num_pixels_x;
		int num_pixels_y;

		CameraSensor * cameraSensor;
	public:
		Camera(Vec3D position, Vec3D angle, int num_pixels_x, int num_pixels_y, float sensor_width, float sensor_height);
		~Camera();
		Vec3D getPixel(int x, int y);
};

}

#endif
