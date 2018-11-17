#include "consts.h"
#include "camerasensor.h"

namespace RayTracer {

CameraSensor::CameraSensor() : RayGenerator(nullptr) {}

CameraSensor::CameraSensor(Scene * const _scene, Surface * const _surface, int _resolution_x, int _resolution_y, float _sensor_dpi) : RayGenerator(_scene) {
	setSurface(_surface);
	setDPI(_sensor_dpi);
	setResolution(_resolution_x, _resolution_y);
}

Vec3 CameraSensor::getPixelPosition(int _x, int _y) {
	Vec3 _position = Vec3(0,0,0);
	Surface * _surface = getSurface();
	if (_surface == nullptr) { return _position; }
	float u = _x/getDPI();
	float v = _y/getDPI();
	_position = _surface->getPointOnSurface(u,v);
	return _position;
}

Vec3 CameraSensor::captureImageData(int _x, int _y) {
	Vec3 _result = Vec3(0,0,0);

	Surface * _surface = getSurface();
	if (_surface == nullptr) { return _result; }

	Vec3 _position = _surface->getPointOnSurface(_x,_y);
	std::experimental::optional<Vec3> _direction = surface->getHitNorm(_position);

	if (!_direction) { return _result; }

	ColorData _colorData = surface->getColorData(_position);

	std::vector<Ray> _rays = generateRays(_position, _direction.value(), GLOBAL_SETTING_RAY_MAX_LIFE, _colorData, GLOBAL_SETTING_RAY_SPREAD, GLOBAL_SETTING_RAY_NUM_SPAWN);
	for (auto _r : _rays) {
		_result += _r.computeResult();
	}

	return _result;
}

int CameraSensor::resolutionX() {
	return resolution_x;
}

int CameraSensor::resolutionY() {
	return resolution_y;
}

float CameraSensor::getDPI() {
	return sensor_dpi;
}

void CameraSensor::setResolution(int _resolution_x, int _resolution_y) {
	resolution_x = _resolution_x;
	resolution_y = _resolution_y;
}

void CameraSensor::setDPI(float _dpi) {
	if (_dpi == 0) { _dpi = 1.0; }
	sensor_dpi = _dpi;
}

void CameraSensor::setScene(Scene * const _scene) {
	RayGenerator::setScene(_scene);
	surface->setScene(_scene);
}

void CameraSensor::setSurface(Surface * const _surface) {
	surface = _surface;
}

Surface * CameraSensor::getSurface() {
	return surface;
}

}
