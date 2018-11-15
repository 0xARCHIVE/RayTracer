#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "object.h"

#include <string>
#include <vector>

namespace RayTracer {

class Scene {
	private:
		std::vector<Camera> cameras;
		std::vector<Object> objects;
	public:
		Scene(std::string configFile, std::string sceneFile);
		void addCamera(Camera& camera);
		void addObject(Object& object);
		std::vector<Camera>& getCameras();
		std::vector<Object>& getObjects();
};

}

#endif
