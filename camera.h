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
		Camera(const Scene& _scene, const Vec3& _position, const Vec3& _angle, CameraSensor _cameraSensor) : Entity(_scene, _position, _angle);
		void setCameraSensor(CameraSensor _cameraSensor);
		cameraSensor& getCameraSensor();
		void captureImage();
		ImageData& getCapturedImage();
};

}

#endif
