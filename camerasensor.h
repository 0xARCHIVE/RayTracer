#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include "surface.h"
#include "vec3d.h"
#include "ray.h"
#include "colordata.h"

namespace RayTracer {

class CameraSensor : public Surface {
	private:
		float sensor_width;
		float sensor_height;
	public:
		CameraSensor(Vec3D position, Vec3D angle, float sensor_width, float sensor_height);
		Vec3D getPixelPosition(int x, int y);

		Vec3D getIntersectionPoint(Ray *r);
		Vec3D getNormal(Vec3D position);
		ColorData getColorData(Vec3D position);
};

}

#endif
