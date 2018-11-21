#include "scene.h"
#include "object.h"
#include "boundingbox.h"
#include "vec3.h"
#include "ray.h"
#include "colordata.h"
#include "plane.h"
#include "quat.h"
#include "file.h"

#include <iostream>
#include <experimental/optional>

using namespace RayTracer;

int main() {
	Scene scene;

	// test objects
	BoundingBox bb1(&scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(10,40,20));
	Object obj1(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb1);

	BoundingBox bb2(&scene, Vec3(0,0,25), Vec3(0,0,0), Vec3(20,20,10));
	Object obj2(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb2);
	//

	// test walls/floor
	BoundingBox bb3(&scene, Vec3(0,50,0), Vec3(0,0,90), Vec3(100,100,1));
	Object obj3(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb3);

	BoundingBox bb4(&scene, Vec3(0,-50,0), Vec3(0,0,90), Vec3(100,100,1));
	Object obj4(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb4);

	BoundingBox bb5(&scene, Vec3(50,0,0), Vec3(90,0,0), Vec3(100,100,1));
	Object obj5(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb5);

	BoundingBox bb6(&scene, Vec3(0,0,-50), Vec3(0,0,0), Vec3(100,100,1));
	Object obj6(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb6);

	BoundingBox bb7(&scene, Vec3(0,0,50), Vec3(0,0,0), Vec3(100,100,1));
	Object obj7(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb7);

	for (auto plane : bb3.getPlanes()) {
		ColorData c = plane->getColorData();
//		c.color = Vec3(1,1,1);
		c.emissivity = 0.25;
		plane->setColorData(c);
	}
	for (auto plane : bb4.getPlanes()) {
		ColorData c = plane->getColorData();
//		c.color = Vec3(1,1,1);
		c.emissivity = 0.25;
		plane->setColorData(c);
	}
	for (auto plane : bb5.getPlanes()) {
		ColorData c = plane->getColorData();
//		c.color = Vec3(1,1,1);
		c.emissivity = 0.25;
		plane->setColorData(c);
	}
	for (auto plane : bb6.getPlanes()) {
		ColorData c = plane->getColorData();
//		c.color = Vec3(1,1,1);
		c.emissivity = 0.25;
		plane->setColorData(c);
	}
	for (auto plane : bb7.getPlanes()) {
		ColorData c = plane->getColorData();
//		c.color = Vec3(1,1,1);
		c.emissivity = 0.25;
		plane->setColorData(c);
	}
	//


	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.reflectivity = 1;
	colorData.transmissivity = 0;
	colorData.multiplier = 1;

	Plane surface(&scene, Vec3(-100,0,25), Vec3(100,10,0), false, true);
	surface.setColorData(colorData);

	CameraSensor sensor(&scene, &surface, 250,250, 1);
	Camera cam(&scene, &sensor);
	cam.captureImage();

//	std::cout << surface.getHitNorm(sensor.getPixelPosition(0,0)).value() << std::endl;
//	std::cout << surface.up() << std::endl;

//	Ray r(&scene, sensor.getPixelPosition(0,0), surface.up(), 2);
//	std::cout << r.getPosition() << " " << r.getDirection() << std::endl;
//	std::experimental::optional<IntersectData> data = scene.getIntersectData(r);
//	if (!data) { std::cout << "no hit" << std::endl; } else {
//		std::cout << "color " << data.value().colorData.color << std::endl;
//		std::cout << "hitpos " << data.value().hitPos << std::endl;
//		std::cout << "hitnorm " << data.value().hitNorm << std::endl;
//		std::cout << "surface pos " << data.value().surface->getPosition() << std::endl;
//		std::cout << "up " <<  data.value().surface->up() << std::endl;
//	}

	File outputFile("output.ppm");
	outputFile.writeImageData(cam.getCapturedImage());

	return 0;
}
