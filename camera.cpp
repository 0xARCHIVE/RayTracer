#include "camera.h"

#include <iostream>
#include <cmath>

namespace RayTracer {

Camera::Camera(Scene * const _scene, CameraSensor * const _cameraSensor) : Entity(_scene, Vec3(0,0,0), Vec3(0,0,0)) {
	setCameraSensor(_cameraSensor);

	runDuration = 0;
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
	if (cameraSensor == nullptr) { runDuration = 0; return; }
	startTime = std::clock();

	capturedImage.RGBvalues = std::vector<Vec3>();
	for (int i = -capturedImage.resolution_x/2; i < capturedImage.resolution_x/2; ++i) {
		if (i % 3 == 0) {
			std::cout << (100.0*(i + capturedImage.resolution_x/2)/capturedImage.resolution_x) << "%" << std::endl;
		}

		for (int j = -capturedImage.resolution_y/2; j < capturedImage.resolution_y/2; ++j) {
			Vec3 _result = cameraSensor->captureImageData(i,j);
			capturedImage.RGBvalues.push_back(_result);
		}
	}

	// https://stackoverflow.com/a/3220503/4000963
	runDuration = (std::clock() - startTime)/(double)CLOCKS_PER_SEC;
}

ImageData& Camera::getCapturedImage() {
	return capturedImage;
}

void Camera::setScene(Scene * const _scene) {
	if (cameraSensor == nullptr) { return; }
	Entity::setScene(_scene);
	cameraSensor->setScene(_scene);
}

double Camera::getRunDuration() const {
	return runDuration;
}

}
