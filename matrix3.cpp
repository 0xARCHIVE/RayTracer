#include "matrix3.h"
#include "vec3.h"

#include <iterator>

namespace RayTracer {

Matrix3::Matrix3() {
	for (int i = 0; i < 9; i++) {
		int x = (i/3) + 1;
		int y = (i%3) + 1;
		set(x,y,0);
	}
}

Matrix3::Matrix3(float _data[9]) {
	std::cout << "test" << std::endl;
	for (int i = 0; i < 9; i++) {
		int x = (i/3) + 1;
		int y = (i%3) + 1;
		set(x,y,_data[i]);
	}
}

Matrix3::Matrix3(float f1,float f2,float f3,float f4,float f5,float f6,float f7,float f8,float f9) {
	set(1,1,f1);
	set(1,2,f2);
	set(1,3,f3);
	set(2,1,f4);
	set(2,2,f5);
	set(2,3,f6);
	set(3,1,f7);
	set(3,2,f8);
	set(3,3,f9);
}

Matrix3::Matrix3(std::vector<float> _data) {
	if (_data.size() != 9) { return; }
	for (int i = 0; i < 9; i++) {
		int x = (i/3) + 1;
		int y = (i%3) + 1;
		set(x,y,_data[i]);
	}
}

void Matrix3::makeIdentity() {
	set(1,1,1);
	set(1,2,0);
	set(1,3,0);

	set(2,1,0);
	set(2,2,1);
	set(2,3,0);

	set(3,1,0);
	set(3,2,0);
	set(3,3,1);
}

float Matrix3::get(int x, int y) const {
	if (x < 1 || x > 3 || y < 1 || y > 3) { return 0; }
	return data[(x-1) + 3*(y-1)];
}

std::vector<float> Matrix3::getAll() const {
	return std::vector<float>{std::begin(data),std::end(data)};
}

void Matrix3::set(int x, int y, float value) {
	if (x < 1 || x > 3 || y < 1 || y > 3) { return; }
	data[(x-1) + 3*(y-1)] = value;
}

float Matrix3::det() {
	return (get(1,1)*( get(2,2)*get(3,3) - get(2,3)*get(3,2) ) - get(1,2)*( get(2,1)*get(3,3) - get(2,3)*get(3,1) ) + get(1,3)*( get(2,1)*get(3,2) - get(2,2)*get(3,1) ));
}

Matrix3 Matrix3::transpose() {
	Matrix3 result;

	result.set(1,1, get(1,1));
	result.set(1,2, get(2,1));
	result.set(1,3, get(3,1));

	result.set(2,1, get(1,2));
	result.set(2,2, get(2,2));
	result.set(2,3, get(3,2));

	result.set(3,1, get(1,3));
	result.set(3,2, get(2,3));
	result.set(3,3, get(3,3));

	return result;
}

Matrix3 Matrix3::adj() {
	Matrix3 result;
	Matrix3 trans = transpose();
	Matrix3 cofactors(1,-1,1,-1,1,-1,1,-1,1);

	result.set(1,1, trans.get(2,2)*trans.get(3,3) - trans.get(2,3)*trans.get(3,2));
	result.set(1,2, trans.get(2,1)*trans.get(3,3) - trans.get(2,3)*trans.get(3,1));
	result.set(1,3, trans.get(2,1)*trans.get(3,2) - trans.get(2,2)*trans.get(3,1));

	result.set(2,1, trans.get(1,2)*trans.get(3,3) - trans.get(1,3)*trans.get(3,2));
	result.set(2,2, trans.get(1,1)*trans.get(3,3) - trans.get(1,3)*trans.get(3,1));
	result.set(2,3, trans.get(1,1)*trans.get(3,2) - trans.get(1,2)*trans.get(3,1));

	result.set(3,1, trans.get(1,2)*trans.get(2,3) - trans.get(1,3)*trans.get(2,2));
	result.set(3,2, trans.get(1,1)*trans.get(2,3) - trans.get(1,3)*trans.get(2,1));
	result.set(3,3, trans.get(1,1)*trans.get(2,2) - trans.get(1,2)*trans.get(2,1));

	return (result.hadamard(cofactors));
}

Matrix3 Matrix3::hadamard(const Matrix3 &m) {
	std::vector<float> lhsData = getAll();
	std::vector<float> rhsData = m.getAll();
	std::vector<float> outData;

	for (int i = 0; i < lhsData.size(); i++) {
		outData.push_back(lhsData[i]*rhsData[i]);
	}

	Matrix3 result(outData);
	return result;
}

std::experimental::optional<Matrix3> Matrix3::inverse() {
	float _det = det();
	if (_det == 0) { return std::experimental::nullopt; }
	Matrix3 result = adj()*(1/_det);
	return std::experimental::optional<Matrix3>(result);
}

Matrix3 &operator+=(Matrix3 &lhs, const Matrix3 &rhs) {
	lhs = lhs + rhs;
	return lhs;
}

const Matrix3 operator+(const Matrix3 &lhs, const Matrix3 &rhs) {
	std::vector<float> lhsData = lhs.getAll();
	std::vector<float> rhsData = rhs.getAll();
	std::vector<float> result;

	for (int i = 0; i < lhsData.size(); i++) {
		result.push_back(lhsData[i] + rhsData[i]);
	}

	Matrix3 output(result);
	return output;
}

Matrix3 &operator-=(Matrix3 &lhs, const Matrix3 &rhs) {
	lhs = lhs - rhs;
	return lhs;
}

const Matrix3 operator-(const Matrix3 &lhs, const Matrix3 &rhs) {
	Matrix3 _rhs = rhs*-1;
	return (lhs + _rhs);
}

Matrix3 &operator*=(Matrix3 &m, float f) {
	m = m*f;
	return m;
}

const Matrix3 operator*(const Matrix3 &m, float f) {
	std::vector<float> mData = m.getAll();
	std::vector<float> result;

	for (int i = 0; i < mData.size(); i++) {
		result.push_back(mData[i]*f);
	}

	Matrix3 output(result);
	return output;
}

Matrix3 &operator*=(float f, Matrix3 &m) {
	m = m*f;
	return m;
}

const Matrix3 operator*(float f, Matrix3 &m) {
	return m*f;
}

const Vec3 operator*(const Matrix3 &m, const Vec3 &v) {
	Vec3 result;

	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();

	float x_result = m.get(1,1)*x + m.get(1,2)*y + m.get(1,3)*z;
	float y_result = m.get(2,1)*x + m.get(2,2)*y + m.get(2,3)*z;
	float z_result = m.get(3,1)*x + m.get(3,2)*y + m.get(3,3)*z;

	result.setX(x_result);
	result.setY(y_result);
	result.setZ(z_result);

	return result;
}

const Vec3 operator*(const Vec3 &v, const Matrix3 &m) {
	Vec3 result;

	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();

	float x_result = m.get(1,1)*x + m.get(2,1)*y + m.get(3,1)*z;
	float y_result = m.get(1,2)*x + m.get(2,2)*y + m.get(3,2)*z;
	float z_result = m.get(1,3)*x + m.get(2,3)*y + m.get(3,3)*z;

	result.setX(x_result);
	result.setY(y_result);
	result.setZ(z_result);

	return result;
}

const Matrix3 operator*(const Matrix3 &lhs, const Matrix3 &rhs) {
	Matrix3 result;

	result.set(1,1,lhs.get(1,1)*rhs.get(1,1) + lhs.get(1,2)*rhs.get(2,1) + lhs.get(1,3)*rhs.get(3,1));
	result.set(1,2,lhs.get(1,1)*rhs.get(1,2) + lhs.get(1,2)*rhs.get(2,2) + lhs.get(1,3)*rhs.get(3,2));
	result.set(1,3,lhs.get(1,1)*rhs.get(1,3) + lhs.get(1,2)*rhs.get(2,3) + lhs.get(1,3)*rhs.get(3,3));

	result.set(2,1,lhs.get(2,1)*rhs.get(1,1) + lhs.get(2,2)*rhs.get(2,1) + lhs.get(2,3)*rhs.get(3,1));
	result.set(2,2,lhs.get(2,1)*rhs.get(1,2) + lhs.get(2,2)*rhs.get(2,2) + lhs.get(2,3)*rhs.get(3,2));
	result.set(2,3,lhs.get(2,1)*rhs.get(1,3) + lhs.get(2,2)*rhs.get(2,3) + lhs.get(2,3)*rhs.get(3,3));

	result.set(3,1,lhs.get(3,1)*rhs.get(1,1) + lhs.get(3,2)*rhs.get(2,1) + lhs.get(3,3)*rhs.get(3,1));
	result.set(3,2,lhs.get(3,1)*rhs.get(1,2) + lhs.get(3,2)*rhs.get(2,2) + lhs.get(3,3)*rhs.get(3,2));
	result.set(3,3,lhs.get(3,1)*rhs.get(1,3) + lhs.get(3,2)*rhs.get(2,3) + lhs.get(3,3)*rhs.get(3,3));

	return result;
}

bool operator==(const Matrix3 &lhs, const Matrix3 &rhs) {
	std::vector<float> lhsData = lhs.getAll();
	std::vector<float> rhsData = rhs.getAll();

	for (int i = 0; i < lhsData.size(); i++) {
		if (lhsData[i] != rhsData[i]) { return false; }
	}

	return true;
}

std::ostream & operator<<(std::ostream &os, const Matrix3 &m) {
	return os << "|" << m.get(1,1) << " " << m.get(1,2) << " " << m.get(1,3) << "|" << std::endl << "|" << m.get(2,1) << " " << m.get(2,2) << " " << m.get(2,3) << "|" << std::endl << "|" << m.get(3,1) << " " << m.get(3,2) << " " << m.get(3,3) << "|";
}

}
