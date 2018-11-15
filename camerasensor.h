#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include "surface.h"
#include "raygenerator.h"

namespace RayTracer {

class CameraSensor : public RayGenerator {
	private:
		Surface surface;
};

}

#endif
