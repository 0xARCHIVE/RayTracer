#ifndef MATRIX3_H
#define MATRIX3_H

#include "vec3.h"

#include <vector>
#include <iostream>
#include <experimental/optional>

namespace RayTracer {

class Matrix3 {
	private:
		float data[9];
	public:
		Matrix3();
		Matrix3(float _data[9]);
		Matrix3(std::vector<float> data);
		Matrix3(float,float,float,float,float,float,float,float,float);

		void makeIdentity();

		float get(int x, int y) const;
		std::vector<float> getAll() const;
		void set(int x, int y, float value);

		Matrix3 hadamard(const Matrix3& m);
		Matrix3 transpose();
		Matrix3 adj();
		float det();
		std::experimental::optional<Matrix3> inverse();
};

Matrix3 &operator+=(Matrix3 &lhs, const Matrix3 &rhs);
const Matrix3 operator+(const Matrix3 &lhs, const Matrix3 &rhs);

Matrix3 &operator-=(Matrix3 &lhs, const Matrix3 &rhs);
const Matrix3 operator-(const Matrix3 &lhs, const Matrix3 &rhs);

Matrix3 &operator*=(Matrix3 &m, float f);
const Matrix3 operator*(const Matrix3 &m, float f);

Matrix3 &operator*=(float f, Matrix3 &m);
const Matrix3 operator*(float f, Matrix3 &m);

const Vec3 operator*(const Matrix3 &m, const Vec3 &v);
const Vec3 operator*(const Vec3 &v, const Matrix3 &m);

const Matrix3 operator*(const Matrix3 &lhs, const Matrix3 &rhs);

bool operator==(const Matrix3 &lhs, const Matrix3 &rhs);

std::ostream &operator<<(std::ostream &os, const Matrix3 &m);

}

#endif
