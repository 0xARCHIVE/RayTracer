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
	Object obj1(&scene, Vec3(0,0,0), Vec3(0,0,0));
	Object obj2(&scene, Vec3(0,0,0), Vec3(0,0,0));
	//

	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.reflectivity = 1;
	colorData.transmissivity = 0;
	colorData.multiplier = 1;

	Vec3 camPos = Vec3(10,0,5);
	Plane surface(&scene, camPos, Vec3(110,170,0), 10,10, true,false);
	surface.setColorData(colorData);

	CameraSensor sensor(&scene, &surface, 200,200, 5);
	Camera cam(&scene, &sensor);
	cam.captureImage();
	std::cout << "Capture took " << cam.getRunDuration() << "s" << std::endl;

	File outputFile("output.ppm");
	outputFile.writeImageData(cam.getCapturedImage());

	return 0;
}
