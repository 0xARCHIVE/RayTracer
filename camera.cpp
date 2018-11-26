#include "camera.h"

#include <iostream>

namespace RayTracer {

Camera::Camera(const CameraSensor sensor) {
	this->setSensor(sensor);
	this->runDuration = 0;
}

void Camera::setSensor(const CameraSensor sensor) {
	this->sensor = sensor;

	this->capturedImage.resolution_x = sensor.getResX();
	this->capturedImage.resolution_y = sensor.getResY();
}

const CameraSensor& Camera::getSensor() const {
	return this->sensor;
}

void Camera::captureImage() {
	this->runDuration = 0;
	startTime = std::clock();

	this->capturedImage.RGBvalues = std::vector<Vec3>();
	for (int i = -this->capturedImage.resolution_x/2; i < this->capturedImage.resolution_x/2; ++i) {
		if (i % 3 == 0) {
			std::cout << (100.0*(i + this->capturedImage.resolution_x/2)/this->capturedImage.resolution_x) << "%" << std::endl;
		}

		for (int j = -this->capturedImage.resolution_y/2; j < this->capturedImage.resolution_y/2; ++j) {
			Vec3 _result = this->getSensor().captureImageData(i,j);
			this->capturedImage.RGBvalues.push_back(_result);
		}
	}

	// https://stackoverflow.com/a/3220503/4000963
	this->runDuration = (std::clock() - startTime)/(double)CLOCKS_PER_SEC;
}

ImageData Camera::getCapturedImage() const {
	return this->capturedImage;
}

double Camera::getRunDuration() const {
	return this->runDuration;
}

}
