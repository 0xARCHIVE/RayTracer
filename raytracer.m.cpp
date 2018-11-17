#include "scene.h"
#include "object.h"
#include "boundingbox.h"
#include "vec3.h"
#include "ray.h"
#include "colordata.h"
#include "plane.h"

#include <iostream>
#include <experimental/optional>

using namespace RayTracer;

int main() {
	Scene scene;

	BoundingBox bb(&scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(10,20,5));
	Object obj(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb);

	ColorData colorData;
	colorData.color = Vec3(1,1,1);
	colorData.emissivity = 0;
	colorData.multiplier = 1;

	Plane surface(&scene, Vec3(0,0,0), Vec3(1,1,1), false, true);
	surface.setColorData(colorData);
	CameraSensor sensor(&scene, Vec3(0,0,0), Vec3(0,0,0), &surface, 10, 10, 1);

	Camera cam(&scene, Vec3(0,0,0), Vec3(0,0,0), &sensor);
	cam.captureImage();

	return 0;
}
