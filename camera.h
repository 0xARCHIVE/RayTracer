#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"
#include "imagedata.h"
#include "camerasensor.h"

#include <ctime>

namespace RayTracer {

class Camera : public Entity {
	protected:
		CameraSensor * cameraSensor;
		ImageData capturedImage;
		std::clock_t startTime;
		double runDuration;
	public:
		Camera(Scene * const _scene, CameraSensor * const _cameraSensor);
		void setCameraSensor(CameraSensor * const _cameraSensor);
		CameraSensor * getCameraSensor();
		void captureImage();
		ImageData& getCapturedImage();
		virtual void setScene(Scene * const _scene);
		double getRunDuration() const;
};

}

#endif
