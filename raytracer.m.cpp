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

	Plane surface(&scene, Vec3(-25,-25,-25), Vec3(0,0,1), false, true);
	surface.setColorData(colorData);
	CameraSensor sensor(&scene, Vec3(-25,-25,-25), Vec3(0,0,0), &surface, 100, 100, 10, 10);
//	Camera cam(&scene, Vec3(-25,-25,25), Vec3(0,0,0), &sensor);

	Ray r(&scene, Vec3(0,0,10), Vec3(0,0,1), 1);
	std::experimental::optional<Vec3> point = surface.getIntersectionPoint(r);
	if (point) {
		std::cout << point.value() << std::endl;
	}

	return 0;
}
