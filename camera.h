#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"
#include "camerasensor.h"

namespace RayTracer {

class Camera : public Entity {
	private:
		CameraSensor cameraSensor;
		std::vector<Vec3> capturedImage;
	public:
		Camera(const Scene& scene, const Vec3& position, const Vec3& angle, CameraSensor cameraSensor);
		void setCameraSensor(CameraSensor cameraSensor);
		cameraSensor& getCameraSensor();
		void captureImage();
		std::vector<Vec3>& getCapturedImage();
};

}

#endif
