#define _USE_MATH_DEFINES

#include "vec3.h"
#include "quat.h"

#include <cmath>

namespace RayTracer {

Vec3::Vec3() {
	this->setX(0);
	this->setY(0);
	this->setZ(0);
}

Vec3::Vec3(double x, double y, double z) {
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}

double Vec3::getX() const {
	return this->x;
}

double Vec3::getY() const {
	return this->y;
}

double Vec3::getZ() const {
	return this->z;
}

void Vec3::setX(double x) {
	this->x = x;
}

void Vec3::setY(double y) {
	this->y = y;
}

void Vec3::setZ(double z) {
	this->z = z;
}

double Vec3::length() const {
	return std::sqrt(std::pow(this->getX(),2) + std::pow(this->getY(),2) + std::pow(this->getZ(),2));
}

double Vec3::dot(const Vec3 &v) const {
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

Vec3 Vec3::rotate(const Vec3 &ang) const {
	return rotate(Quat(ang));
}

Vec3 Vec3::rotate(const Quat &q) const {
	Quat qnorm = q.normalised();
	Quat qconj = qnorm.conjugate();
	return (qnorm*((*this)*qconj)).toVector();
}


Vec3 Vec3::angleToDirection() const {
	// rotate "forward" (1,0,0) to the angle and that's where we're pointing
	return Vec3(1,0,0).rotate(Quat((*this)));
}

Vec3 Vec3::directionToAngle() const {
	// find quat between (1,0,0) and us, and convert it to angle
	if (length() == 0) { return Vec3(0,0,0); }

	Quat q;
	q = q.quatBetween(Vec3(1,0,0),*this);
	return q.toAngle();
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

const Vec3 operator-(const Vec3 &v) {
	return (-1*v);
}

Vec3 &operator*=(Vec3 &v, double f) {
	v = v*f;
	return v;
}

const Vec3 operator*(const Vec3 &v, double f) {
	Vec3 output;
	output.setX(v.getX()*f);
	output.setY(v.getY()*f);
	output.setZ(v.getZ()*f);
	return output;
}

Vec3 &operator*=(double f, Vec3 &v) {
	v = v*f;
	return v;
}

const Vec3 operator*(double f, const Vec3 &v) {
	return v*f;
}

bool operator==(const Vec3 &lhs, const Vec3 &rhs) {
	return ((lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY()) && (lhs.getZ() == rhs.getZ()));
}

std::ostream &operator<<(std::ostream &os, const Vec3 &v) {
	return os << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
}

}
