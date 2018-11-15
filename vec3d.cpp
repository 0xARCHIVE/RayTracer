#include "vec3d.h"

#include <cmath>

namespace RayTracer {

Vec3D::Vec3D() {
	this->setX(0);
	this->setY(0);
	this->setZ(0);
}

Vec3D::Vec3D(float x, float y, float z) {
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}

float Vec3D::getX() const {
	return this->x;
}

float Vec3D::getY() const {
	return this->y;
}

float Vec3D::getZ() const {
	return this->z;
}

void Vec3D::setX(float x) {
	this->x = x;
}

void Vec3D::setY(float y) {
	this->y = y;
}

void Vec3D::setZ(float z) {
	this->z = z;
}

float Vec3D::length() {
	return std::sqrt(std::pow(this->getX(),2) + std::pow(this->getY(),2) + std::pow(this->getZ(),2));
}

float Vec3D::dot(const Vec3D &v) {
	return (this->getX()*v.getX() + this->getY()*v.getY() + this->getZ()*v.getZ());
}

Vec3D Vec3D::cross(const Vec3D &v) {
	Vec3D output;
	output.setX( this->getY()*v.getZ() - this->getZ()*v.getY() );
	output.setY( this->getZ()*v.getX() - this->getX()*v.getZ() );
	output.setZ( this->getX()*v.getY() - this->getY()*v.getX() );
	return output;
}

Vec3D Vec3D::hadamard(const Vec3D &v) {
	Vec3D output;
	output.setX( this->getX()*v.getX() );
	output.setY( this->getY()*v.getY() );
	output.setZ( this->getZ()*v.getZ() );
	return output;
}

Vec3D &operator+=(Vec3D &lhs, const Vec3D &rhs) {
	lhs = lhs + rhs;
	return lhs;
}

const Vec3D operator+(const Vec3D &lhs, const Vec3D &rhs) {
	Vec3D output;
	output.setX(lhs.getX() + rhs.getX());
	output.setY(lhs.getY() + rhs.getY());
	output.setZ(lhs.getZ() + rhs.getZ());
	return output;
}

Vec3D &operator-=(Vec3D &lhs, const Vec3D &rhs) {
	lhs = lhs - rhs;
	return lhs;
}

const Vec3D operator-(const Vec3D &lhs, const Vec3D &rhs) {
	Vec3D output;
	output.setX(lhs.getX() - rhs.getX());
	output.setY(lhs.getY() - rhs.getY());
	output.setZ(lhs.getZ() - rhs.getZ());
	return output;
}

Vec3D &operator*=(Vec3D &v, float f) {
	v = v*f;
	return v;
}

const Vec3D operator*(const Vec3D &v, float f) {
	Vec3D output;
	output.setX(v.getX()*f);
	output.setY(v.getY()*f);
	output.setZ(v.getZ()*f);
	return output;
}

Vec3D &operator*=(float f, Vec3D &v) {
	v = v*f;
	return v;
}

const Vec3D operator*(float f, const Vec3D &v) {
	return v*f;
}

bool operator==(const Vec3D &lhs, const Vec3D &rhs) {
	return ((lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY()) && (lhs.getZ() == rhs.getZ()));
}

std::ostream &operator<<(std::ostream &os, const Vec3D &v) {
	return os << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
}

}
