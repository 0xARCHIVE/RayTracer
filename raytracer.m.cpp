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
	Scene scene;
	// test objects
	std::shared_ptr<Entity> obj1 = std::make_shared<Entity>(Vec3(0,0,0),Vec3(0,0,0));

	std::shared_ptr<Box> box1 = std::make_shared<Box>(Vec3(0,0,0), Vec3(0,0,0), Vec3(50,50,50));
	std::shared_ptr<Box> box2 = std::make_shared<Box>(Vec3(0,0,0), Vec3(45,45,45), Vec3(100,100,1));
	std::shared_ptr<Box> box3 = std::make_shared<Box>(Vec3(0,0,0), Vec3(-45,45,45), Vec3(100,100,1));

	obj1->addChild(box1);
	obj1->addChild(box2);
	obj1->addChild(box3);

	scene.addEnt(obj1);
	//

	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.reflectivity = 1;
	colorData.transmissivity = 0;
	colorData.multiplier = 1;

	Vec3 camPos = Vec3(-100,-60,100);
	std::shared_ptr<Plane> surface = std::make_shared<Plane>(camPos, Vec3(130,35,0),0,0);
	surface->setColor(colorData);

	CameraSensor sensor(surface, 192,108, 1);
	std::shared_ptr<Camera> cam = std::make_shared<Camera>(sensor);
	scene.addCam(cam);

	cam->captureImage();
	std::cout << "Capture took " << cam->getRunDuration() << "s" << std::endl;

	File outputFile("output.ppm");
	outputFile.writeImageData(cam->getCapturedImage());

	return 0;
}
