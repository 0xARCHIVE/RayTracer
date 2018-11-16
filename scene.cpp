#include "scene.h"

void Scene::addCamera(const Camera& _camera) {
	this->cameras.push_back(_camera);
	_camera.setScene(*this);
}

void Scene::addObject(const Object& object) {
	this->objects.push_back(object);
	_object.setScene(*this);
}

std::vector<Camera>& Scene::getCameras() {
	return this->cameras;
}

std::vector<Object>& Scene::getObjects() {
	return this->objects;
}

void Scene::captureImages() {
	for (auto const& camera: this->cameras) {
		camera.captureImage();
	}
}

std::vector<std::reference_wrapper<ImageData>> Scene::getCapturedImages() {
	std::vector<std::reference_wrapper<ImageData>> output;
	for (auto const& camera: this->cameras) {
		output.push_back(camera.getCapturedImage());
	}
	return output;
}
