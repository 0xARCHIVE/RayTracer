#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

#include <vector>

namespace RayTracer {

class Scene {
	private:
		std::vector<Camera> cameras;
		std::vector<Object> objects;
};

}

#endif
