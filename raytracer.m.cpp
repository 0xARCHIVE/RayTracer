#include "scene.h"
#include "object.h"
#include "boundingbox.h"
#include "vec3.h"
#include "ray.h"
#include "colordata.h"
#include "plane.h"
#include "quat.h"

#include <iostream>
#include <experimental/optional>

using namespace RayTracer;

int main() {
/*	Scene scene;

	BoundingBox bb(&scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(10,20,5));
	Object obj(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb);

	std::cout << bb.forward() << std::endl;
	std::cout << bb.right() << std::endl;
	std::cout << bb.up() << std::endl;

	std::cout << std::endl;

	std::vector<Plane *> planes = bb.getPlanes();
	for (auto plane : planes) {
		std::cout << plane->getPosition() << " | " << plane->getNorm() << " | " << plane->getAngle() << std::endl;
	}

	std::cout << std::endl;

	bb.rotate(Vec3(45,0,0));

	std::cout << bb.forward() << std::endl;
	std::cout << bb.right() << std::endl;
	std::cout << bb.up() << std::endl;
	std::cout << std::endl;

//	bb.setPosition(Vec3(10,0,0));
	for (auto plane : planes) {
		std::cout << plane->getPosition() << " | " << plane->getNorm() << " | " << plane->getAngle() << std::endl;
	}

	std::cout << std::endl;
//
//	ColorData colorData;
//	colorData.color = Vec3(1,1,1);
//	colorData.emissivity = 0;
//	colorData.reflectivity = 1;
//	colorData.transmissivity = 0;
//
//	Plane surface(&scene, Vec3(0,0,0), Vec3(45,0,0), false, true);
//	surface.setColorData(colorData);
//
//	CameraSensor sensor(&scene, &surface, 10, 10, 1);
//	Camera cam(&scene, &sensor);
//	cam.captureImage();

	Vec3 v1(1,2,3);
	Vec3 v2(4,5,6);
	Vec3 v3(7,8,9);

	Vec3 v11(1,0,0);
	Vec3 v22(0,1,0);
	Vec3 v33(0,0,1);

	Matrix3 m(v1,v2,v3);
	std::cout << m*v11 << std::endl;
	std::cout << m*v22 << std::endl;
	std::cout << m*v33 << std::endl;

	std::cout << v11.transform(m) << std::endl;
	std::cout << v22.transform(m) << std::endl;
	std::cout << v33.transform(m) << std::endl;
*/

	Scene scene;
	BoundingBox bb(&scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(10,20,5));

	std::vector<Plane *> planes = bb.getPlanes();
	std::cout << "===" << std::endl;
	for (auto plane : planes) {
		std::cout << plane->getPosition() << " | " << plane->getNorm() << " | " << plane->getAngle() << " | " << plane->toWorld(Vec3(0,0,1)) << " = " << plane->getPosition() + plane->up() << std::endl;
	}
	std::cout << "===" << std::endl;

	std::cout << std::endl;
	bb.rotate(Vec3(45,0,0));

	std::cout << "===" << std::endl;
	for (auto plane : planes) {
		std::cout << plane->getPosition() << " | " << plane->getNorm() << " | " << plane->getAngle() << " | " << plane->toWorld(Vec3(0,0,1)) << " = " << plane->getPosition() + plane->up() << std::endl;
	}
	std::cout << "===" << std::endl;

/*
	std::cout << std::endl;

	std::cout << bb.getToWorldTransformation() << std::endl;

	std::cout << std::endl;

	bb.rotate(Vec3(45,0,0));

	std::cout << bb.forward() << std::endl;
	std::cout << bb.right() << std::endl;
	std::cout << bb.up() << std::endl;

	std::cout << std::endl;

	std::cout << bb.forward() << std::endl;
	std::cout << bb.right() << std::endl;
	std::cout << bb.up() << std::endl;
*/

	return 0;
}
