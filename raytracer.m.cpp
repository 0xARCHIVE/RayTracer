#include "scene.h"
#include "object.h"
#include "boundingbox.h"
#include "vec3.h"
#include "ray.h"
#include "colordata.h"
#include "plane.h"
#include "quat.h"
#include "file.h"

#include <cmath>
#include <iostream>
#include <experimental/optional>

using namespace RayTracer;

int main() {
	Scene scene;

	// test objects
	BoundingBox bb1(&scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(20,20,1));
	Object obj1(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb1);

	BoundingBox bb2(&scene, Vec3(0,0,5), Vec3(0,0,0), Vec3(5,5,5));
	Object obj2(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb2);
	//

	// test walls/floor
	BoundingBox bb3(&scene, Vec3(0,50,0), Vec3(0,0,90), Vec3(100,100,1));
	Object obj3(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb3);

	BoundingBox bb4(&scene, Vec3(0,-50,0), Vec3(0,0,90), Vec3(100,100,1));
	Object obj4(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb4);

	BoundingBox bb5(&scene, Vec3(50,0,0), Vec3(90,0,0), Vec3(100,100,1));
	Object obj5(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb5);

	BoundingBox bb6(&scene, Vec3(-50,0,0), Vec3(90,0,0), Vec3(100,100,1));
	Object obj6(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb6);

	BoundingBox bb7(&scene, Vec3(0,0,50), Vec3(0,0,0), Vec3(100,100,1));
	Object obj7(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb7);

	BoundingBox bb8(&scene, Vec3(0,0,-50), Vec3(0,0,0), Vec3(100,100,1));
	Object obj8(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb8);

	for (auto plane : bb3.getPlanes()) {
		ColorData c = plane->getColorData();
		c.color = Vec3(0.25,0.5,0.5);
//		c.color = Vec3(1,1,1);
		c.emissivity = 1;
		plane->setColorData(c);
	}
	for (auto plane : bb4.getPlanes()) {
		ColorData c = plane->getColorData();
		c.color = Vec3(0.5,0.5,0.25);
//		c.color = Vec3(1,1,1);
		c.emissivity = 0;
		plane->setColorData(c);
	}
	for (auto plane : bb5.getPlanes()) {
		ColorData c = plane->getColorData();
		c.color = Vec3(0.5,0.25,0.5);
//		c.color = Vec3(1,1,1);
		c.emissivity = 0;
		plane->setColorData(c);
	}
	for (auto plane : bb6.getPlanes()) {
		ColorData c = plane->getColorData();
		c.color = Vec3(0.25,0.5,0.25);
//		c.color = Vec3(1,1,1);
		c.emissivity = 1;
		plane->setColorData(c);
	}
	for (auto plane : bb7.getPlanes()) {
		ColorData c = plane->getColorData();
		c.color = Vec3(0.5,0.25,0.25);
		c.emissivity = 1;
		plane->setColorData(c);
	}
	//
	for (auto plane : bb8.getPlanes()) {
		ColorData c = plane->getColorData();
		c.color = Vec3(0.25,0.25,0.5);
//		c.color = Vec3(1,1,1);
		c.emissivity = 1;
		plane->setColorData(c);
	}
	//


	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.reflectivity = 1;
	colorData.transmissivity = 0;
	colorData.multiplier = 1;

	Vec3 camPos = Vec3(10,0,5);
	Plane surface(&scene, camPos, Vec3(110,170,0), false, true);
	surface.setColorData(colorData);

	CameraSensor sensor(&scene, &surface, 100,100, 1);
	Camera cam(&scene, &sensor);
	cam.captureImage();
	std::cout << "Capture took " << cam.getRunDuration() << "s" << std::endl;

	File outputFile("output.ppm");
	outputFile.writeImageData(cam.getCapturedImage());

	return 0;
}
