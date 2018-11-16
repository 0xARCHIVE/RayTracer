#include "object.h"

Object::Object(const Scene* _scene, const Vec3& _position, const Vec3& _angle, BoundingBox _boundingBox) : Entity(_scene, _position, _angle) {}

void Object::setScene(const Scene* _scene) {
	Entity::setScene(_scene);
	BoundingBox.setScene(_scene);
	for (auto surface : surfaces) {
		surface.setScene(_scene);
	}
}
