#include "scene.h"
#include "box.h"
#include "object.h"
#include "boundingbox.h"
#include "vec3.h"
#include "ray.h"
#include "colordata.h"
#include "plane.h"
#include "quat.h"
#include "file.h"
#include "camerasensor.h"
#include "camera.h"

#include <cmath>
#include <iostream>
#include <experimental/optional>

using namespace RayTracer;

int main() {
	Scene scene;

	// test objects
	Object obj1(&scene, Vec3(0,0,0), Vec3(0,0,0));

	Box box1(&scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(50,50,50));
	Box box2(&scene, Vec3(0,0,0), Vec3(45,45,45), Vec3(100,100,1));
	Box box3(&scene, Vec3(0,0,0), Vec3(-45,45,45), Vec3(100,100,1));

	obj1.addSurface(&box1);
	obj1.addSurface(&box2);
	obj1.addSurface(&box3);
	//

	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.reflectivity = 1;
	colorData.transmissivity = 0;
	colorData.multiplier = 1;

	Vec3 camPos = Vec3(-100,0,100);
	Plane surface(&scene, camPos, Vec3(135,10,0), 0,0, true,false);
	surface.setColorData(colorData);

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


	CameraSensor sensor(&scene, &surface, 200,200, 1);
	Camera cam(&scene, &sensor);
//	cam.captureImage();
	std::cout << "Capture took " << cam.getRunDuration() << "s" << std::endl;

	File outputFile("output.ppm");
	outputFile.writeImageData(cam.getCapturedImage());

	return 0;
}
