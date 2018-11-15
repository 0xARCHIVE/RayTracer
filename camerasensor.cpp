#include "camerasensor.h"

CameraSensor::CameraSensor(Vec3D position, Vec3D angle, float sensor_width, float sensor_height) {

}

Vec3D CameraSensor::getPixelPosition(int x, int y) {

}

Vec3D CameraSensor::getIntersectionPoint(Ray *r) {

}

Vec3D CameraSensor::getNormal(Vec3D position) {

}

ColorData CameraSensor::getColorData(Vec3D position) {
	ColorData colorData;
	colorData.color = Vec3D(255,255,255);
	colorData.emissivity = 0;
	colorData.multiplier = 1;
	return colorData;
}
