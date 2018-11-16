#include "object.h"

namespace RayTracer {

Object::Object(Scene * const _scene, const Vec3& _position, const Vec3& _angle, BoundingBox * const _boundingBox) : Entity(_scene, _position, _angle) {}

void Object::addSurface(Surface * const _surface) {
	surfaces.push_back(_surface);
}

std::vector<Surface *>& Object::getSurfaces() {
	return surfaces;
}

void Object::setBoundingBox(BoundingBox * const _boundingBox) {
	boundingBox = _boundingBox;
}

BoundingBox * Object::getBoundingBox() {
	return boundingBox;
}

void Object::setScene(Scene * const _scene) {
	Entity::setScene(_scene);
	boundingBox->setScene(_scene);
	for (auto surface : surfaces) {
		surface->setScene(_scene);
	}
}

}
