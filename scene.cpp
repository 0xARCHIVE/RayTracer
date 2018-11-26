#include "scene.h"
#include "consts.h"
#include "boundingbox.h"
#include "ray.h"
#include "intersectdata.h"
#include "imagedata.h"
#include "camera.h"
#include "object.h"

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
	IntersectData intersection;
	double dist = 0;
	bool found = false;
	for (auto object : getObjects()) {
		if (object == nullptr) { continue; }
		if (!object->doesRayHitBB(_r)) { continue; }

		std::experimental::optional<IntersectData> intersect_opt = object->intersect(_r);
		if (!intersect_opt) { continue; }
		Vec3 dV = (intersect_opt.value().hitPos - _r.getPosition());
		double _dist = dV.length();

		if (!found || dist > (_dist + GLOBAL_SETTING_RAY_PRECISION)) {
			dist = _dist;
			intersection = intersect_opt.value();
			found = true;
		}
	}

	if (found) { return intersection; }
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
