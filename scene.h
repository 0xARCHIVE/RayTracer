#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

#include <string>

namespace RayTracer {

class Scene {
	public:
		Scene(std::string config_file, std::string scene_file);
};

}

#endif
