#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"
#include "camerasensor.h"

namespace RayTracer {

class Camera : public Entity {
	private:
		CameraSensor cameraSensor;
};

}

#endif
