#include "scene.h"
#include "entity.h"
#include "box.h"
#include "colordata.h"
#include "camera.h"
#include "plane.h"
#include "camerasensor.h"
#include "vec3.h"
#include "file.h"

#include <iostream>

using namespace RayTracer;

int main() {
	ColorData c;
	c.color = Vec3(1,0.25,0.25);
	c.emissivity = 0.5;
	c.reflectivity = 0;
	c.transmissivity = 0;
	c.multiplier = 1;

	ColorData c2 = c;
	c2.color = Vec3(1,1,1);
	c2.reflectivity = 1.0;
	c2.emissivity = 0.0;

	Scene scene;
	// test objects
	std::shared_ptr<Entity> obj1 = std::make_shared<Entity>(Vec3(0,0,0),Vec3(0,0,0));

	std::shared_ptr<Box> box1 = std::make_shared<Box>(Vec3(0,0,0), Vec3(0,0,0), Vec3(50,50,50));
	std::shared_ptr<Box> box2 = std::make_shared<Box>(Vec3(0,0,0), Vec3(45,45,45), Vec3(100,100,1));
	std::shared_ptr<Box> box3 = std::make_shared<Box>(Vec3(0,0,0), Vec3(-45,45,45), Vec3(100,100,1));
	std::shared_ptr<Box> box4 = std::make_shared<Box>(Vec3(0,0,0), Vec3(0,0,0), Vec3(2000,2000,2000));

	std::shared_ptr<Plane> p1 = std::make_shared<Plane>(Vec3(300,0,0), Vec3(1000,0,0), 2000,2000);
	p1->setColor(c);
	scene.addEnt(p1);

	std::shared_ptr<Plane> p2 = std::make_shared<Plane>(Vec3(200,0,0), Vec3(90,0,0), 100,100);
	p2->setColor(c2);
	scene.addEnt(p2);

	obj1->addChild(box1);
	obj1->addChild(box2);
	obj1->addChild(box3);
	obj1->addChild(box4);

	scene.addEnt(obj1);
	//

	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.reflectivity = 1;
	colorData.transmissivity = 0;
	colorData.multiplier = 1;

//	Vec3 camPos = Vec3(-200,-120,200);
//	std::shared_ptr<Plane> surface = std::make_shared<Plane>(camPos, Vec3(130,30,0),0,0);
	Vec3 camPos = Vec3(-300,100,120);
	std::shared_ptr<Plane> surface = std::make_shared<Plane>(camPos, Vec3(110,-20,0),0,0);
	surface->setColor(colorData);

	CameraSensor sensor(surface, 192,108, 0.5);
	std::shared_ptr<Camera> cam = std::make_shared<Camera>(sensor);
	scene.addCam(cam);

	cam->captureImage();
	std::cout << "Capture took " << cam->getRunDuration() << "s" << std::endl;

	File outputFile("output.ppm");
	outputFile.writeImageData(cam->getCapturedImage());

	return 0;
}
