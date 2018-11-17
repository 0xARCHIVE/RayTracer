#include "camera.h"
#include <iostream>

namespace RayTracer {

Camera::Camera(Scene * const _scene, CameraSensor * const _cameraSensor) : Entity(_scene, Vec3(0,0,0), Vec3(0,0,0)) {
	setCameraSensor(_cameraSensor);
}

void Camera::setCameraSensor(CameraSensor * const _cameraSensor) {
	if (_cameraSensor == nullptr) { return; }
	cameraSensor = _cameraSensor;
	capturedImage.resolution_x = cameraSensor->resolutionX();
	capturedImage.resolution_y = cameraSensor->resolutionY();
}

CameraSensor * Camera::getCameraSensor() {
	return cameraSensor;
}

void Camera::captureImage() {
	if (cameraSensor == nullptr) { return; }

	capturedImage.RGBvalues = std::vector<Vec3>();
	for (int i = 0; i < capturedImage.resolution_x; i++) {
		for (int j = 0; j < capturedImage.resolution_y; j++) {
			Vec3 _result = cameraSensor->captureImageData(i,j);
			std::cout << "pixel " << i << " " << j << " = " << _result << std::endl;
			capturedImage.RGBvalues.push_back(_result);
		}
	}
}

ImageData& Camera::getCapturedImage() {
	return capturedImage;
}

void Camera::setScene(Scene * const _scene) {
	if (cameraSensor == nullptr) { return; }
	Entity::setScene(_scene);
	cameraSensor->setScene(_scene);
}

}
