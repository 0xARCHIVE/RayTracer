#include "object.h"
#include "scene.h"
#include "boundingbox.h"

#include <iostream>

namespace RayTracer {

Object::Object(Scene * const _scene, const Vec3& _position, const Vec3& _angle, BoundingBox * const _boundingBox) : Entity(_scene, _position, _angle) {
	_scene->addObject(this);
	setBoundingBox(_boundingBox);
}

void Object::addSurface(Surface * const _surface) {
	if (_surface == nullptr) { return; }
	surfaces.push_back(_surface);
	addChild(_surface);
}

std::vector<Surface *>& Object::getSurfaces() {
	return surfaces;
}

void Object::setBoundingBox(BoundingBox * const _boundingBox) {
	if (_boundingBox == nullptr) { return; }
	boundingBox = _boundingBox;
	addChild(_boundingBox);
}

BoundingBox * Object::getBoundingBox() {
	return boundingBox;
}

}
