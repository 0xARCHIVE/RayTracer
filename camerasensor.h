#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

namespace RayTracer {

class CameraSensor {
	private:
		Surface surface;
		RayFactory rayfactory;

		int resX;
		int resY;
		double dpi;

		Vec3 getPixelPos(int x, int y) const;

	public:
		CameraSensor();
		CameraSensor(const Surface &surface, int resX = 0, int resY = 0, double dpi = 1);

		void setSurface(const Surface &surface);
		const Surface& getSurface() const;

		void setDPI(double dpi);
		double getDPI() const;

		void setRes(int resX, int resY);
		int getResX() const;
		int getResY() const;

		Vec3 captureImageData(int x, int y) const;
};

}

#endif
