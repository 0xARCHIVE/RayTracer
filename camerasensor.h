#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include "surface.h"

#include <memory>

namespace RayTracer {

class RayFactory;
class Vec3;

class CameraSensor {
	private:
		Scene * scene;

		std::shared_ptr<Surface> surface;
		std::shared_ptr<RayFactory> rayfactory;

		int resX;
		int resY;
		double dpi;

		Vec3 getPixelPos(int x, int y) const;

	public:
		CameraSensor();
		CameraSensor(std::shared_ptr<Surface> surface, int resX = 0, int resY = 0, double dpi = 1);

		void setScene(Scene * scene);

		void setSurface(std::shared_ptr<Surface> surface);
		std::shared_ptr<Surface> getSurface() const;

		void setDPI(double dpi);
		double getDPI() const;

		void setRes(int resX, int resY);
		int getResX() const;
		int getResY() const;

		Vec3 captureImageData(int x, int y) const;
};

}

#endif
