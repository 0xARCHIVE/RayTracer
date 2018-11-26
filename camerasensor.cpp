#include "camerasensor.h"
#include "consts.h"
#include "ray.h"
#include "rayfactory.h"

#include <experimental/optional>

namespace RayTracer {

CameraSensor::CameraSensor() {}

CameraSensor::CameraSensor(std::shared_ptr<const Surface> surface, int resX, int resY, double dpi) {
	this->rayfactory = std::make_shared<RayFactory>(surface->getScene());
	this->setSurface(surface);
	this->setRes(resX,resY);
	this->setDPI(dpi);
}

void CameraSensor::setSurface(std::shared_ptr<const Surface> surface) {
	this->surface = surface;
}

std::shared_ptr<const Surface> CameraSensor::getSurface() const {
	return this->surface;
}

void CameraSensor::setDPI(double dpi) {
	this->dpi = dpi;
}

double CameraSensor::getDPI() const {
	return this->dpi;
}

void CameraSensor::setRes(int resX, int resY) {
	this->resX = resX;
	this->resY = resY;
}

int CameraSensor::getResX() const {
	return this->resX;
}

int CameraSensor::getResY() const {
	return this->resY;
}

Vec3 CameraSensor::captureImageData(int x, int y) const {
	Vec3 result = Vec3(0,0,0);

	Vec3 pos = this->getPixelPos(x,y);
	std::experimental::optional<Vec3> direction = this->getSurface()->getNorm(pos);
	if (!direction) { return result; }

	ColorData color = this->getSurface()->getColor(pos);
	std::vector<std::shared_ptr<Ray>> rays = this->rayfactory->generateRays(pos,direction.value(),GLOBAL_SETTING_RAY_MAX_LIFE + 1,color,0,1);

	for (auto ray : rays) {
		result += ray->computeResult();
	}

	return result*(1.0/rays.size());
}

Vec3 CameraSensor::getPixelPos(int x, int y) const {
	double u = x/this->getDPI();
	double v = y/this->getDPI();
	return this->getSurface()->getPointOnSurface(u,v);
}

}
