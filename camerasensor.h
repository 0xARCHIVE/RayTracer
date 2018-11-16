#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include "surface.h"
#include "raygenerator.h"

namespace RayTracer {

class CameraSensor : public RayGenerator {
	protected:
		Surface* surface;
		int resolution_x;
		int resolution_y;
		float sensor_width;
		float sensor_height;
	public:
		CameraSensor();
		CameraSensor(Scene * const _scene, const Vec3& _position, const Vec3& _angle, Surface * const _surface, int _resolution_x, int _resolution_y, float _sensor_width, float _sensor_height);
		Vec3 getPixelPosition(int _x, int _y);	// returns world position of pixel (x,y) on the sensor
		Vec3 captureImageData(int _x, int _y);	// returns (R,G,B) capture result from pixel (x,y)
		int resolutionX();
		int resolutionY();
		virtual void setScene(Scene * const _scene);
		void setSurface(Surface * const _surface);
};

}

#endif
