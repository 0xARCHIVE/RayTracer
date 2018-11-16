#include "entity.h"

namespace RayTracer {

Entity::Entity(Scene * const _scene, const Vec3& _position, const Vec3& _angle) {
	setPosition(_position);
	setAngle(_angle);
	setScene(_scene);
}

void Entity::setScene(Scene * const _scene) {
	scene = _scene;
}

void Entity::setPosition(const Vec3& _position) {
	position = _position;
}

void Entity::setAngle(const Vec3& _angle) {
	angle = _angle;
}

Scene* Entity::getScene() const {
	return scene;
}

Vec3 Entity::getPosition() const {
	return position;
}

Vec3 Entity::getAngle() const {
	return angle;
}

}
