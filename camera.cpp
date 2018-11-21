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
	for (int i = -capturedImage.resolution_x/2; i < capturedImage.resolution_x/2; i++) {
		std::cout << (100.0*(i + capturedImage.resolution_x/2)/capturedImage.resolution_x) << "%" << std::endl;
		for (int j = -capturedImage.resolution_y/2; j < capturedImage.resolution_y/2; j++) {
			Vec3 _result = cameraSensor->captureImageData(i,j);
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
