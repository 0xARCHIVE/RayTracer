#ifndef VEC3_H
#define VEC3_H

#include <ostream>

namespace RayTracer {

class Quat;

class Vec3 {
	private:
		double x;
		double y;
		double z;
	public:
		Vec3();
		Vec3(double x, double y, double z);

		double getX() const;
		double getY() const;
		double getZ() const;

		void setX(double x);
		void setY(double y);
		void setZ(double z);

		double length() const;
		double dot(const Vec3& v) const;
		Vec3 abs() const;
		Vec3 cross(const Vec3& v) const;
		Vec3 hadamard(const Vec3& v) const;
		Vec3 normalised() const;
		Vec3 angleToDirection() const;
		Vec3 directionToAngle() const;

		Vec3 rotate(const Vec3 &ang) const;
		Vec3 rotate(const Quat &q) const;

		Vec3 randomSpread(double angle) const;
};

Vec3 &operator+=(Vec3 &lhs, const Vec3 &rhs);
const Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs);

Vec3 &operator-=(Vec3 &lhs, const Vec3 &rhs);
const Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs);

const Vec3 operator-(const Vec3 &v);

Vec3 &operator*=(Vec3 &v, double f);
const Vec3 operator*(const Vec3 &v, double f);

Vec3 &operator*=(double f, Vec3 &v);
const Vec3 operator*(double f, const Vec3 &v);

bool operator==(const Vec3 &lhs, const Vec3 &rhs);

std::ostream &operator<<(std::ostream &os, const Vec3 &v);

}

#endif
