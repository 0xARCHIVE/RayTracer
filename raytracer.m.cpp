#include "scene.h"
#include "object.h"
#include "boundingbox.h"
#include "vec3.h"
#include "ray.h"
#include "colordata.h"
#include "plane.h"
#include "matrix3.h"

#include <iostream>
#include <experimental/optional>

using namespace RayTracer;

int main() {
/*	Scene scene;

	BoundingBox bb(&scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(10,20,5));
//	Object obj(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb);

//	bb.setPosition(Vec3(10,0,0));
	std::vector<Plane *> planes = bb.getPlanes();
	for (auto plane : planes) {
		std::cout << plane->getPosition() << " | " << plane->getNorm() << std::endl;
	}

	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.reflectivity = 1;
	colorData.transmissivity = 0;

	Plane surface(&scene, Vec3(0,0,0), Vec3(45,0,0), false, true);
	surface.setColorData(colorData);

	CameraSensor sensor(&scene, &surface, 10, 10, 1);
	Camera cam(&scene, &sensor);
//	cam.captureImage();
*/

	float test[9] = {5,6,7,3,8,5,8,9,3};
//	std::vector<float> test({1,2,3,4,5,6,7,8,9});
	Matrix3 m1(test);
//	Matrix3 m1(1,2,3,4,5,6,7,8,9);
//	Matrix3 m1(1,0,0,0,1,0,0,0,1);

//	Matrix3 m2;
	Matrix3 m2(9,8,7,6,5,4,3,2,1);
//	m2.makeIdentity();

	std::cout << m1 << std::endl;
	std::cout << std::endl;
	std::cout << m2 << std::endl;
	std::cout << std::endl;
	std::cout << m1*m2 << std::endl;
	std::cout << std::endl;
	std::cout << m1.det() << std::endl;
	std::cout << std::endl;
	std::cout << m1*(m1.inverse().value()) << std::endl;


	return 0;
}
