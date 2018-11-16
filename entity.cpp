#include "entity.h"

Entity::Entity(const Scene* _scene, const Vec3& _position, const Vec3& _angle) {
	Entity(_position,_angle);
	setScene(_scene);
}

void Entity::setScene(const Scene* _scene) {
	scene = _scene;
}

void Entity::setPosition(const Vec3& _position) {
	position = _position;
}

void Entity::setAngle(const Vec3& _angle) {
	angle = _angle;
}

Scene* Entity::getScene() {
	return scene;
}

Vec3 Entity::getPosition() {
	return position;
}

Vec3 Entity::getAngle() {
	return angle;
}
