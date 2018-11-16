#include "camera.h"

namespace RayTracer {

Camera::Camera(Scene * const _scene, const Vec3& _position, const Vec3& _angle, CameraSensor _cameraSensor) : Entity(_scene, _position, _angle) {
	setCameraSensor(_cameraSensor);
}

void Camera::setCameraSensor(CameraSensor _cameraSensor) {
	cameraSensor = _cameraSensor;
	capturedImage.resolution_x = cameraSensor.resolutionX();
	capturedImage.resolution_y = cameraSensor.resolutionY();
}

CameraSensor& Camera::getCameraSensor() {
	return cameraSensor;
}

void Camera::captureImage() {
	capturedImage.RGBvalues = std::vector<Vec3>();
	for (int i = 0; i < capturedImage.resolution_x; i++) {
		for (int j = 0; j < capturedImage.resolution_y; j++) {
			capturedImage.RGBvalues.push_back(cameraSensor.captureImageData(i,j));
		}
	}
}

ImageData& Camera::getCapturedImage() {
	return capturedImage;
}

void Camera::setScene(Scene * const _scene) {
	Entity::setScene(_scene);
	cameraSensor.setScene(_scene);
}

}
