#include "scene.h"
#include "consts.h"
#include "boundingbox.h"

#include <iostream>

namespace RayTracer {

Scene::Scene() {}

void Scene::addCamera(Camera * const _camera) {
	if (_camera == nullptr) { return; }
	this->cameras.push_back(_camera);
	_camera->setScene(this);
}

void Scene::addObject(Object * const _object) {
	if (_object == nullptr) { return; }
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
	IntersectData intersection;
	double dist = 0;
	bool found = false;
	for (auto object : objects) {
		if (object == nullptr) { continue; }
		BoundingBox* bb = object->getBoundingBox();
		if (bb == nullptr) { continue; }
		if (!bb->canIntersectRays()) { continue; }
		std::experimental::optional<IntersectData> intersect_opt = bb->intersect(_r);
		// TODO ADD SURFACE INTERSECTION //

		if (!intersect_opt) { continue; }
		Vec3 _dir = (intersect_opt.value().hitPos - _r.getPosition());
		double _dist = _dir.length();
//		std::cout << intersect_opt.value().hitPos << "\t" << _r.getPosition() << "\t" << _dir << "\t" << _r.getDirection() << "\t" << _dir.dot(_r.getDirection()) << std::endl;
		if (_dir.dot(_r.getDirection()) < 0) { // hitPos is behind the ray, ignore
			continue;
		}

		if (!found || abs(dist) > _dist + GLOBAL_SETTING_RAY_PRECISION) {
			dist = _dist;
			intersection = intersect_opt.value();
			found = true;
		}
	}

	if (found) {
		return intersection;
	}
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
