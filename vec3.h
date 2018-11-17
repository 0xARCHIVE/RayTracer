#ifndef VEC3_H
#define VEC3_H

#include <ostream>

namespace RayTracer {

class Vec3 {
	private:
		float x;
		float y;
		float z;
	public:
		Vec3();
		Vec3(float x, float y, float z);

		float getX() const;
		float getY() const;
		float getZ() const;

		void setX(float x);
		void setY(float y);
		void setZ(float z);

		float length() const;
		float dot(const Vec3& v) const;
		Vec3 cross(const Vec3& v) const;
		Vec3 hadamard(const Vec3& v) const;
		Vec3 normalised() const;
		Vec3 angleToDirection() const;
		Vec3 directionToAngle() const;

		Vec3 rotate(const Vec3& _angle) const;
};

Vec3 &operator+=(Vec3 &ls, const Vec3 &rhs);
const Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs);

Vec3 &operator-=(Vec3 &lhs, const Vec3 &rhs);
const Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs);

Vec3 &operator*=(Vec3 &v, float f);
const Vec3 operator*(const Vec3 &v, float f);

Vec3 &operator*=(float f, Vec3 &v);
const Vec3 operator*(float f, const Vec3 &v);

bool operator==(const Vec3 &lhs, const Vec3 &rhs);

std::ostream &operator<<(std::ostream &os, const Vec3 &v);

}

#endif
