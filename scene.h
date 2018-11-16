#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "object.h"
#include "imagedata.h"
#include "intersectdata.h"

#include <functional>
#include <string>
#include <vector>

namespace RayTracer {

class Scene {
	protected:
		std::vector<Camera> cameras;
		std::vector<Object> objects;
	public:
		Scene(std::vector<Camera> cameras, std::vector<Object> _objects);
		void addCamera(const Camera& _camera);
		void addObject(const Object& _object);
		std::vector<Camera>& getCameras();
		std::vector<Object>& getObjects();
		void captureImages();
		std::vector<std::reference_wrapper<ImageData>> getCapturedImages();
		IntersectData getIntersectData(const Ray& _r);
};

}

#endif
