#include "camerasensor.h"

namespace RayTracer {

CameraSensor::CameraSensor() : RayGenerator(nullptr) {}

CameraSensor::CameraSensor(Scene * const _scene, const Vec3& _position, const Vec3& _angle, Surface * const _surface, int _resolution_x, int _resolution_y, float _sensor_width, float _sensor_height) : RayGenerator(_scene) {
	setSurface(_surface);
}

Vec3 CameraSensor::getPixelPosition(int _x, int _y) {
	// TODO
	return Vec3(0,0,0);
}

Vec3 CameraSensor::captureImageData(int _x, int _y) {
	// TODO
	return Vec3(0,0,0);
}

int CameraSensor::resolutionX() {
	return resolution_x;
}

int CameraSensor::resolutionY() {
	return resolution_y;
}

void CameraSensor::setScene(Scene * const _scene) {
	RayGenerator::setScene(_scene);
	surface->setScene(_scene);
}

void CameraSensor::setSurface(Surface * const _surface) {
	surface = _surface;
}

}
