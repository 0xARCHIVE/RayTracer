#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include "surface.h"
#include "raygenerator.h"
#include "surface.h"

namespace RayTracer {

class CameraSensor : public RayGenerator {
	protected:
		Surface* surface;
		int resolution_x;
		int resolution_y;
		double sensor_dpi;
	public:
		CameraSensor();
		CameraSensor(Scene * const _scene, Surface * const _surface, int _resolution_x, int _resolution_y, double _sensor_dpi);
		Vec3 getPixelPosition(int _x, int _y);	// returns world position of pixel (x,y) on the sensor
		Vec3 captureImageData(int _x, int _y);	// returns (R,G,B) capture result from pixel (x,y)
		int resolutionX();
		int resolutionY();
		double getDPI();
		void setResolution(int _resolution_x, int _resolution_y);
		void setDPI(double _dpi);
		virtual void setScene(Scene * const _scene);
		void setSurface(Surface * const _surface);
		Surface * getSurface();
};

}

#endif
