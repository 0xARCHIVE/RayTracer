#include "camerasensor.h"

void CameraSensor::setScene(const *Scene _scene) {
	RayGenerator::setScene(_scene);
	surface.setScene(_scene);
}
