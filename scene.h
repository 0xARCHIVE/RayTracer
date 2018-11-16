#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "object.h"
#include "imagedata.h"
#include "intersectdata.h"

#include <experimental/optional>
#include <functional>
#include <string>
#include <vector>

namespace RayTracer {

class Scene {
	protected:
		std::vector<Camera*> cameras;
		std::vector<Object*> objects;
	public:
		Scene();
		void addCamera(Camera * const _camera);
		void addObject(Object * const _object);
		std::vector<Camera*>& getCameras();
		std::vector<Object*>& getObjects();
		void captureImages();
		std::vector<std::reference_wrapper<ImageData>> getCapturedImages();
		std::experimental::optional<IntersectData> getIntersectData(const Ray& _r);
};

}

#endif
