#include "scene.h"
#include "camera.h"

namespace RayTracer {

Scene::Scene() {
	this->kdnode = std::make_shared<KDNode>();
}

void Scene::addCam(std::shared_ptr<Camera> cam) {
	cam->setScene(this);
	this->cameras.push_back(cam);
}

void Scene::addEnt(std::shared_ptr<Entity> ent) {
	ent->setScene(this);
	this->ents.push_back(ent);
	this->recalculateKDtree();
}

std::vector<std::shared_ptr<Camera>> Scene::getCams() const {
	return this->cameras;
}

std::vector<std::shared_ptr<Entity>> Scene::getEnts() const {
	return this->ents;
}

void Scene::captureImages() {
	for (auto const& camera: this->getCams()) {
		camera->captureImage();
	}
}

std::vector<ImageData> Scene::getCapturedImages() {
	std::vector<ImageData> output;
	for (auto const& camera: this->getCams()) {
		output.push_back(camera->getCapturedImage());
	}
	return output;
}

void Scene::recalculateKDtree() {
	this->kdnode->build(this->getEnts());
}

std::experimental::optional<IntersectData> Scene::intersectRay(const Ray &r) const {
	return kdnode->intersectRay(r);
}

}
