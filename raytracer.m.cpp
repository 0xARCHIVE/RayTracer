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
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

	// test objects
	Entity obj1(scene, Vec3(0,0,0), Vec3(0,0,0));

	std::shared_ptr<Box> box1 = std::make_shared<Box>(scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(50,50,50));
	std::shared_ptr<Box> box2 = std::make_shared<Box>(scene, Vec3(0,0,0), Vec3(45,45,45), Vec3(100,100,1));
	std::shared_ptr<Box> box3 = std::make_shared<Box>(scene, Vec3(0,0,0), Vec3(-45,45,45), Vec3(100,100,1));

	obj1.addChild(box1);
	obj1.addChild(box2);
	obj1.addChild(box3);
	//

	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.reflectivity = 1;
	colorData.transmissivity = 0;
	colorData.multiplier = 1;

	Vec3 camPos = Vec3(-100,0,100);
	std::shared_ptr<Plane> surface = std::make_shared<Plane>(scene, camPos, Vec3(135,10,0),0,0);
	surface->setColor(colorData);

//	Plane* plane = box1.getPlanes()[0];
//	Ray r(&scene,Vec3(0,0,5+1.2),Vec3(1,0.25,-0.25),1);
//	std::cout << r.computeResult() << std::endl;
//	std::cout << plane->getWidth() << " " << plane->getHeight() << std::endl;
//	std::cout << plane->getPosition() << std::endl;
//	std::cout << plane->getNorm() << " " << plane->right() << " " << plane->forward() << std::endl;
//
//	Vec3 point = plane->getIntersectionPoint(r).value();
//	Vec3 dV = (point - plane->getPosition());
//	std::cout << "point = " << point << std::endl;
//	std::cout << "dV = " << plane->toLocal(point) << std::endl;
//	Vec3 dV = plane->toLocal(point);
//	std::cout << "width " << std::abs(dV.dot( Vec3(0,1,0) )) << std::endl;
//	std::cout << "height " << std::abs(dV.dot( Vec3(1,0,0) )) << std::endl;
//
//
//	IntersectData d = plane->getIntersectData(r,true,false).value();
//	ColorData c = d.colorData;
//	std::cout << c.multiplier << std::endl;
//	std::cout << c.transmissivity << std::endl;
//	std::cout << c.emissivity << std::endl;
//	std::cout << c.reflectivity << std::endl;


	CameraSensor sensor(surface, 200,200, 1);
	Camera cam(sensor);
//	cam.captureImage();
	std::cout << "Capture took " << cam.getRunDuration() << "s" << std::endl;

	File outputFile("output.ppm");
	outputFile.writeImageData(cam.getCapturedImage());

	return 0;
}
