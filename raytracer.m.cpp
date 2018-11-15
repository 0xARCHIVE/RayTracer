#include "vec3d.h"
#include "camera.h"

#include <iostream>

int main() {
	RayTracer::Vec3D pos(0,0,0);
	RayTracer::Vec3D dir(0,0,1);
	RayTracer::Camera camera(pos, dir, 10, 100, 10, 100);

	return 0;
}
