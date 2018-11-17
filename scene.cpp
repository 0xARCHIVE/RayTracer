#include "scene.h"

namespace RayTracer {

Scene::Scene() {}

void Scene::addCamera(Camera * const _camera) {
	this->cameras.push_back(_camera);
	_camera->setScene(this);
}

void Scene::addObject(Object * const _object) {
	this->objects.push_back(_object);
	_object->setScene(this);
}

std::vector<Camera*>& Scene::getCameras() {
	return this->cameras;
}

std::vector<Object*>& Scene::getObjects() {
	return this->objects;
}

void Scene::captureImages() {
	for (auto const& camera: this->cameras) {
		camera->captureImage();
	}
}

std::experimental::optional<IntersectData> Scene::getIntersectData(const Ray& _r) {
	// TODO - boundingbox intersection tests and KD tree optimisation
	return std::experimental::nullopt;
}

std::vector<std::reference_wrapper<ImageData>> Scene::getCapturedImages() {
	std::vector<std::reference_wrapper<ImageData>> output;
	for (auto const& camera: this->cameras) {
		output.push_back(camera->getCapturedImage());
	}
	return output;
}

}
