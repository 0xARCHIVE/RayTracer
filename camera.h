#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"
#include "imagedata.h"
#include "camerasensor.h"

namespace RayTracer {

class Camera : public Entity {
	protected:
		CameraSensor cameraSensor;
		ImageData capturedImage;
	public:
		Camera(Scene * const _scene, const Vec3& _position, const Vec3& _angle, CameraSensor _cameraSensor);
		void setCameraSensor(CameraSensor _cameraSensor);
		CameraSensor& getCameraSensor();
		void captureImage();
		ImageData& getCapturedImage();
		virtual void setScene(Scene * const _scene);
};

}

#endif
