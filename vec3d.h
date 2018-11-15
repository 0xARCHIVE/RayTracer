#ifndef VEC3D_H
#define VEC3D_H

#include <ostream>

namespace RayTracer {

class Vec3D {
	private:
		float x;
		float y;
		float z;
	public:
		Vec3D();
		Vec3D(float x, float y, float z);

		float getX() const;
		float getY() const;
		float getZ() const;

		void setX(float x);
		void setY(float y);
		void setZ(float z);

		float length();
		float dot(const Vec3D &v);
		Vec3D cross(const Vec3D &v);
		Vec3D hadamard(const Vec3D &v);
};

Vec3D &operator+=(Vec3D &ls, const Vec3D &rhs);
const Vec3D operator+(const Vec3D &lhs, const Vec3D &rhs);

Vec3D &operator-=(Vec3D &lhs, const Vec3D &rhs);
const Vec3D operator-(const Vec3D &lhs, const Vec3D &rhs);

Vec3D &operator*=(Vec3D &v, float f);
const Vec3D operator*(const Vec3D &v, float f);

Vec3D &operator*=(float f, Vec3D &v);
const Vec3D operator*(float f, const Vec3D &v);

bool operator==(const Vec3D &lhs, const Vec3D &rhs);

std::ostream &operator<<(std::ostream &os, const Vec3D &v);

}

#endif
