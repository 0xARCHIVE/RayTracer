#include "camera.h"

Camera::Camera(Vec3D position, Vec3D angle, int num_pixels_x, int num_pixels_y, float sensor_width, float sensor_height) {
	this->position = position;
	this->angle = angle;

	this->num_pixels_x = num_pixels_x;
	this->num_pixels_y = num_pixels_y;

	this->cameraSensor = new CameraSensor(position, angle, sensor_width, sensor_height);
}

Camera::~Camera() {
	delete this->cameraSensor;
}

Camera::getPixel(int x, int y) {
	// tell sensor to spawn rays from itself at pixel (x,y) and get the result
}
