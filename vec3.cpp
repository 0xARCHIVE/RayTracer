#define _USE_MATH_DEFINES

#include "vec3.h"

#include "math.h"

namespace RayTracer {

Vec3::Vec3() {
	this->setX(0);
	this->setY(0);
	this->setZ(0);
}

Vec3::Vec3(float x, float y, float z) {
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}

float Vec3::getX() const {
	return this->x;
}

float Vec3::getY() const {
	return this->y;
}

float Vec3::getZ() const {
	return this->z;
}

void Vec3::setX(float x) {
	this->x = x;
}

void Vec3::setY(float y) {
	this->y = y;
}

void Vec3::setZ(float z) {
	this->z = z;
}

float Vec3::length() const {
	return std::sqrt(std::pow(this->getX(),2) + std::pow(this->getY(),2) + std::pow(this->getZ(),2));
}

float Vec3::dot(const Vec3 &v) const {
	return (this->getX()*v.getX() + this->getY()*v.getY() + this->getZ()*v.getZ());
}

Vec3 Vec3::cross(const Vec3 &v) const {
	Vec3 output;
	output.setX( this->getY()*v.getZ() - this->getZ()*v.getY() );
	output.setY( this->getZ()*v.getX() - this->getX()*v.getZ() );
	output.setZ( this->getX()*v.getY() - this->getY()*v.getX() );
	return output;
}

Vec3 Vec3::hadamard(const Vec3 &v) const {
	Vec3 output;
	output.setX( this->getX()*v.getX() );
	output.setY( this->getY()*v.getY() );
	output.setZ( this->getZ()*v.getZ() );
	return output;
}

Vec3 Vec3::normalised() const {
	if (this->length() == 0) { return (*this); }
	return (*this)*(1.0/this->length());
}

Vec3 Vec3::angleToDirection() const {
	float alpha = getX()*(M_PI/180);
	float beta = getY()*(M_PI/180);
	return Vec3(cos(alpha)*cos(beta), sin(alpha)*cos(beta), sin(beta)).normalised();
}

Vec3 Vec3::directionToAngle() const {
	if (length() == 0) { return Vec3(0,0,0); }

	float x = getX();
	float y = getY();
	float z = getZ();

	float pitch = (180/M_PI)*acos(z/length());
	float yaw = (180/M_PI)*atan2(y,x);
	float roll = 0;

	return Vec3(pitch,yaw,roll);
}

Vec3 Vec3::rotate(const Vec3& _angle) const {
	// https://en.wikipedia.org/wiki/Rotation_formalisms_in_three_dimensions
	// TODO: make a matrix library

	float _pitch = -1*_angle.getX()*(M_PI/180);
	float _yaw = _angle.getZ()*(M_PI/180);
	float _roll = _angle.getY()*(M_PI/180);

	float _x = getX();
	float _y = getY();
	float _z = getZ();

	Vec3 result(0,0,0);

	result.setX( _x*(cos(_pitch)*cos(_roll)) + _y*(-cos(_yaw)*sin(_roll) + sin(_yaw)*sin(_pitch)*cos(_roll)) + _z*(sin(_yaw)*sin(_roll) + cos(_yaw)*sin(_pitch)*cos(_roll)) );
	result.setY( _x*(cos(_pitch)*sin(_roll)) + _y*(cos(_yaw)*cos(_roll) + sin(_yaw)*sin(_pitch)*sin(_roll)) + _z*(-sin(_yaw)*cos(_roll) + cos(_yaw)*sin(_pitch)*sin(_roll)) );
	result.setZ( _x*(-sin(_pitch)) + _y*(sin(_yaw)*cos(_pitch)) + _z*(cos(_yaw)*cos(_pitch)) );

	return result;
}

Vec3 &operator+=(Vec3 &lhs, const Vec3 &rhs) {
	lhs = lhs + rhs;
	return lhs;
}

const Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs) {
	Vec3 output;
	output.setX(lhs.getX() + rhs.getX());
	output.setY(lhs.getY() + rhs.getY());
	output.setZ(lhs.getZ() + rhs.getZ());
	return output;
}

Vec3 &operator-=(Vec3 &lhs, const Vec3 &rhs) {
	lhs = lhs - rhs;
	return lhs;
}

const Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs) {
	return (lhs + (-1*rhs));
}

Vec3 &operator*=(Vec3 &v, float f) {
	v = v*f;
	return v;
}

const Vec3 operator*(const Vec3 &v, float f) {
	Vec3 output;
	output.setX(v.getX()*f);
	output.setY(v.getY()*f);
	output.setZ(v.getZ()*f);
	return output;
}

Vec3 &operator*=(float f, Vec3 &v) {
	v = v*f;
	return v;
}

const Vec3 operator*(float f, const Vec3 &v) {
	return v*f;
}

bool operator==(const Vec3 &lhs, const Vec3 &rhs) {
	return ((lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY()) && (lhs.getZ() == rhs.getZ()));
}

std::ostream &operator<<(std::ostream &os, const Vec3 &v) {
	return os << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
}

}
