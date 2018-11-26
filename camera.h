#ifndef CAMERA_H
#define CAMERA_H

#include "camerasensor.h"
#include "imagedata.h"

#include <ctime>
#include <memory>

namespace RayTracer {

class Camera {
	private:
		CameraSensor sensor;
		ImageData capturedImage;

		std::clock_t startTime;
		double runDuration;

	public:
		Camera(const CameraSensor sensor);

		void setSensor(const CameraSensor sensor);
		const CameraSensor& getSensor() const;

		void captureImage();
		ImageData getCapturedImage() const;

		double getRunDuration() const;
};

}

#endif
