#ifndef QUAT_H
#define QUAT_H

#include <ostream>

namespace RayTracer {

class Vec3;
class Quat {
	// https://en.wikipedia.org/wiki/Quaternion
	private:
		double r;
		double i;
		double j;
		double k;
	public:
		Quat();
		Quat(double r, double i, double j, double k);
		Quat(const Vec3 &axis, double ang);
		Quat(const Vec3 &ang);

		double getReal() const;
		double getR() const;
		double getI() const;
		double getJ() const;
		double getK() const;

		void setR(double r);
		void setI(double i);
		void setJ(double j);
		void setK(double k);

		Vec3 toVector() const;
		Vec3 toAngle() const;
		Quat quatBetween(const Vec3 &v1, const Vec3 &v2) const;

		Quat conjugate() const;
		Quat inverse() const;
		double norm() const;
		Quat hamiltonProduct(const Quat &rhs) const;
		Quat normalised() const;
};

Quat &operator+=(Quat &lhs, const Quat &rhs);
const Quat operator+(const Quat &lhs, const Quat &rhs);

Quat &operator-=(Quat &lhs, const Quat &rhs);
const Quat operator-(const Quat &lhs, const Quat &rhs);

const Quat operator-(const Quat &q);

Quat &operator*=(Quat &q, double f);
const Quat operator*(const Quat &q, double f);

Quat &operator*=(double f, Quat &q);
const Quat operator*(double f, const Quat &q);

Quat &operator*=(Quat &lhs, const Quat &rhs);
const Quat operator*(const Quat &lhs, const Quat &rhs);

Quat &operator*=(Quat &q, const Vec3 &v);
const Quat operator*(const Vec3 &v, const Quat &q);
const Quat operator*(const Quat &q, const Vec3 &v);

bool operator==(const Quat &lhs, const Quat &rhs);

std::ostream &operator<<(std::ostream &os, const Quat &q);

}

#endif
