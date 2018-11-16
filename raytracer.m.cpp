#include "scene.h"
#include "object.h"
#include "boundingbox.h"
#include "vec3.h"
#include "ray.h"
#include "colordata.h"
#include "plane.h"

#include <iostream>

using namespace RayTracer;

int main() {
	Scene scene;

	BoundingBox bb(&scene, Vec3(0,0,0), Vec3(0,0,0), Vec3(10,20,5));
	Object obj(&scene, Vec3(0,0,0), Vec3(0,0,0), &bb);

	Plane surface(&scene, Vec3(-25,-25,-25), Vec3(0,0,1), false, true);
//	CameraSensor sensor(&scene, Vec3(-25,-25,-25), Vec3(0,0,0), &surface, 100, 100, 10, 10);
//	Camera cam(&scene, Vec3(-25,-25,25), Vec3(0,0,0), &sensor);

//	ColorData colorData;
//	Ray r(&scene, Vec3(20,0,0), Vec3(0,0,1), 1, colorData);

	return 0;
}
