#define _USE_MATH_DEFINES

#include "quat.h"
#include "vec3.h"

#include <iostream>
#include <cmath>

namespace RayTracer {

Quat::Quat() {
	this->setR(0);
	this->setI(0);
	this->setJ(0);
	this->setK(0);
}

Quat::Quat(double _r, double _i, double _j, double _k) {
	this->setR(_r);
	this->setI(_i);
	this->setJ(_j);
	this->setK(_k);
}

Quat::Quat(const Vec3 &_axis, double _ang) {
	Vec3 scaled = _axis.normalised()*sin(_ang/2.0);

	setR(cos(_ang/2.0));
	setI(scaled.getX());
	setJ(scaled.getY());
	setK(scaled.getZ());
}

Quat::Quat(const Vec3 &_ang) {
	// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Euler_Angles_to_Quaternion_Conversion
	double roll = _ang.getX()*(M_PI/180.0);
	double pitch = _ang.getY()*(M_PI/180.0);
	double yaw = _ang.getZ()*(M_PI/180.0);

	Quat qp = Quat(Vec3(0,1,0),roll);
	Quat qy = Quat(Vec3(0,0,1),pitch);
	Quat qr = Quat(Vec3(1,0,0),yaw);

	Quat q = qy*qp*qr;
	setR(q.getR());
	setI(q.getI());
	setJ(q.getJ());
	setK(q.getK());
}

/*double Quat::getR() const {
	return this->r;
}

double Quat::getI() const {
	return this->i;
}

double Quat::getJ() const {
	return this->j;
}

double Quat::getK() const {
	return this->k;
}*/

void Quat::setR(double _r) {
	this->r = _r;
}

void Quat::setI(double _i) {
	this->i = _i;
}

void Quat::setJ(double _j) {
	this->j = _j;
}

void Quat::setK(double _k) {
	this->k = _k;
}

Vec3 Quat::toVector() const {
	return Vec3(getI(),getJ(),getK());
}

Vec3 Quat::toAngle() const {
	// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles#Quaternion_to_Euler_Angles_Conversion
	double q0 = getR();
	double q1 = getI();
	double q2 = getJ();
	double q3 = getK();

	double roll = (180/M_PI)*atan2(2*(q0*q1 + q2*q3), 1 - 2*(q1*q1 + q2*q2));
	double pitch = (180/M_PI)*asin(2*(q0*q2 - q3*q1));
	double yaw = (180/M_PI)*atan2(2*(q0*q3 + q1*q2), 1 - 2*(q2*q2 + q3*q3));

	return Vec3(pitch,yaw,roll);
}

Quat Quat::quatBetween(const Vec3 &v1, const Vec3 &v2) const {
	// https://stackoverflow.com/a/1171995/4000963
	Vec3 cross = v1.cross(v2);

	Quat q;
	q.setI(cross.getX());
	q.setJ(cross.getY());
	q.setK(cross.getZ());
	q.setR(v1.length()*v2.length() + v1.dot(v2));
	q = q.normalised();

	return q;
}

Quat Quat::conjugate() const {
	return Quat(getR(),-getI(),-getJ(),-getK());
}

Quat Quat::inverse() const {
	return ( conjugate() * (1/pow(norm(),2)) );
}

double Quat::norm() const {
	return (sqrt( pow(getR(),2) + pow(getI(),2) + pow(getJ(),2) + pow(getK(),2) ));
}

Quat Quat::hamiltonProduct(const Quat &rhs) const {
	double a1 = getR();
	double b1 = getI();
	double c1 = getJ();
	double d1 = getK();

	double a2 = rhs.getR();
	double b2 = rhs.getI();
	double c2 = rhs.getJ();
	double d2 = rhs.getK();

	double _r = a1*a2 - b1*b2 - c1*c2 - d1*d2;
	double _i = a1*b2 + b1*a2 + c1*d2  - d1*c2;
	double _j = a1*c2 - b1*d2 + c1*a2  + d1*b2;
	double _k = a1*d2 + b1*c2 - c1*b2 + d1*a2;

	return Quat(_r,_i,_j,_k);
}

Quat Quat::normalised() const {
	return ((*this)*(1/norm()));
}

Quat &operator+=(Quat &lhs, const Quat &rhs) {
	lhs = lhs + rhs;
	return lhs;
}

const Quat operator+(const Quat &lhs, const Quat &rhs) {
	Quat output;
	output.setR(lhs.getR() + rhs.getR());
	output.setI(lhs.getI() + rhs.getI());
	output.setJ(lhs.getJ() + rhs.getJ());
	output.setK(lhs.getK() + rhs.getK());
	return output;
}

Quat &operator-=(Quat &lhs, const Quat &rhs) {
	lhs = lhs - rhs;
	return lhs;
}

const Quat operator-(const Quat &lhs, const Quat &rhs) {
	return (lhs + (-1*rhs));
}

const Quat operator-(const Quat &q) {
	return (-1*q);
}

Quat &operator*=(Quat &q, double f) {
	q = q*f;
	return q;
}

const Quat operator*(const Quat &q, double f) {
	Quat output;
	output.setR(q.getR()*f);
	output.setI(q.getI()*f);
	output.setJ(q.getJ()*f);
	output.setK(q.getK()*f);
	return output;
}

Quat &operator*=(double f, Quat &q) {
	q = q*f;
	return q;
}

const Quat operator*(double f, const Quat &q) {
	return q*f;
}

Quat &operator*=(Quat &lhs, const Quat &rhs) {
	lhs = lhs.hamiltonProduct(rhs);
	return lhs;
}

const Quat operator*(const Quat &lhs, const Quat &rhs) {
	return 	lhs.hamiltonProduct(rhs);
}

Quat &operator*=(Quat &q, const Vec3 &v) {
	q = q.hamiltonProduct(Quat(0,v.getX(),v.getY(),v.getZ()));
	return q;
}

const Quat operator*(const Vec3 &v, const Quat &q) {
	return 	Quat(0,v.getX(),v.getY(),v.getZ()).hamiltonProduct(q);
}

const Quat operator*(const Quat &q, const Vec3 &v) {
	return 	q.hamiltonProduct(Quat(0,v.getX(),v.getY(),v.getZ()));
}

bool operator==(const Quat &lhs, const Quat &rhs) {
	return ((lhs.getR() == rhs.getR()) && (lhs.getI() == rhs.getI()) && (lhs.getJ() == rhs.getJ()) && (lhs.getK() == rhs.getK()));
}

std::ostream &operator<<(std::ostream &os, const Quat &q) {
	return os << "(" << q.getR() << "," << q.getI() << "," << q.getJ() << "," << q.getK() << ")";
}

}
