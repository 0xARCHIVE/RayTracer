#include "vec3d.h"

#include <assert.h>
#include <iostream>

int main() {
	RayTracer::Vec3D v1(0,0,0);
	RayTracer::Vec3D v2(10,0,0);
	RayTracer::Vec3D v3(0,0,5);
	RayTracer::Vec3D v4(0,0,5);

	assert(v1.getX() == 0);
	assert(v1.getY() == 0);
	assert(v1.getZ() == 0);

	assert(v2.getX() == 10);
	assert(v2.getY() == 0);
	assert(v2.getZ() == 0);

	assert(v3.getX() == 0);
	assert(v3.getY() == 0);
	assert(v3.getZ() == 5);

	v1.setX(3);
	v1.setY(4);
	v1.setZ(0);

	assert(v1.getX() == 3);
	assert(v1.getY() == 4);
	assert(v1.getZ() == 0);

	assert(v1.length() == 5);

	assert(v2.dot(v3) == 0);
	assert(v1.dot(v2) == 30);

	assert(v3 == v4);

	v1.setX(3);
	v1.setY(4);
	v1.setZ(1);
	v3.setX(20);
	v3.setY(-2);
	v3.setZ(5);
	assert(v1.cross(v3) == RayTracer::Vec3D(22,5,-86));
	assert(v1.hadamard(v3) == RayTracer::Vec3D(60,-8,5));
	assert(v1*5 == RayTracer::Vec3D(15,20,5));
	v1*=-1;
	assert(v1 == RayTracer::Vec3D(-3,-4,-1));
	v1+=v3;
	assert(v1 == RayTracer::Vec3D(17,-6,4));
	assert(v3 == RayTracer::Vec3D(20,-2,5));

	std::cout << "Vec3D tests passed" << std::endl;

	return 0;
}
