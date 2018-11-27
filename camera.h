#ifndef CAMERA_H
#define CAMERA_H

#include "camerasensor.h"
#include "imagedata.h"

#include <ctime>
#include <memory>

namespace RayTracer {

class Camera {
	private:
		Scene * scene;

		CameraSensor sensor;
		ImageData capturedImage;

		std::clock_t startTime;
		double runDuration;

	public:
		Camera(const CameraSensor sensor);

		void setScene(Scene * scene);

		void setSensor(const CameraSensor sensor);
		const CameraSensor& getSensor() const;
		CameraSensor& getSensor();

		void captureImage();
		ImageData getCapturedImage() const;

		double getRunDuration() const;
};

}

#endif
