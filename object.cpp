#include "object.h"

namespace RayTracer {

Object::Object(Scene * const _scene, const Vec3& _position, const Vec3& _angle, BoundingBox * const _boundingBox) : Entity(_scene, _position, _angle) {
	setBoundingBox(_boundingBox);
}

void Object::addSurface(Surface * const _surface) {
	if (_surface == nullptr) { return; }
	surfaces.push_back(_surface);
}

std::vector<Surface *>& Object::getSurfaces() {
	return surfaces;
}

void Object::setBoundingBox(BoundingBox * const _boundingBox) {
	if (_boundingBox == nullptr) { return; }
	boundingBox = _boundingBox;
}

BoundingBox * Object::getBoundingBox() {
	return boundingBox;
}

void Object::setScene(Scene * const _scene) {
	if (_scene == nullptr) { return; }

	Entity::setScene(_scene);

	if (boundingBox != nullptr) {
		boundingBox->setScene(_scene);
	}

	for (auto surface : surfaces) {
		if (surface == nullptr) { continue; }
		surface->setScene(_scene);
	}
}

}
