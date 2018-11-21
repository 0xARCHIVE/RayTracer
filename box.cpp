#include "box.h"
#include "plane.h"

#include <iostream>
#include <cstdlib>

namespace RayTracer {

Box::Box(Scene* const _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions, bool _canIntersectRays, bool _canGenerateRays) : ConvexPolygon(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	dimensions = _dimensions;

	double depth = _dimensions.getX();
	double width = _dimensions.getY();
	double height = _dimensions.getZ();

	Plane * p1 = new Plane(_scene, toWorld(Vec3(depth/2,0,0)), _angle + Vec3(90,0,0), _canIntersectRays, _canGenerateRays);
	Plane * p2 = new Plane(_scene, toWorld(Vec3(-depth/2,0,0)), _angle + Vec3(-90,0,0), _canIntersectRays, _canGenerateRays);
	Plane * p3 = new Plane(_scene, toWorld(Vec3(0,width/2,0)), _angle + Vec3(0,0,-90), _canIntersectRays, _canGenerateRays);
	Plane * p4 = new Plane(_scene, toWorld(Vec3(0,-width/2,0)), _angle + Vec3(0,0,90), _canIntersectRays, _canGenerateRays);
	Plane * p5 = new Plane(_scene, toWorld(Vec3(0,0,height/2)), _angle, _canIntersectRays, _canGenerateRays);
	Plane * p6 = new Plane(_scene, toWorld(Vec3(0,0,-height/2)), _angle + Vec3(0,0,180), _canIntersectRays, _canGenerateRays);

	// testing
	ColorData c;
	c.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
	c.emissivity = 0.1;
	c.reflectivity = 0.7;
	c.transmissivity = 0;
	c.multiplier = 1;

	ColorData c1 = c;
	ColorData c2 = c;
	ColorData c3 = c;
	ColorData c4 = c;
	ColorData c5 = c;
	ColorData c6 = c;

//	c1.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
//	c2.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
//	c3.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
//	c4.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
//	c5.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
//	c6.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));

	p1->setColorData(c1);
	p2->setColorData(c2);
	p3->setColorData(c3);
	p4->setColorData(c4);
	p5->setColorData(c5);
	p6->setColorData(c6);
	//

	addPlane(p1);
	addPlane(p2);
	addPlane(p3);
	addPlane(p4);
	addPlane(p5);
	addPlane(p6);

	planesToDelete.push_back(p1);
	planesToDelete.push_back(p2);
	planesToDelete.push_back(p3);
	planesToDelete.push_back(p4);
	planesToDelete.push_back(p5);
	planesToDelete.push_back(p6);
}

Box::~Box() {
	for (auto plane : planesToDelete) {
		delete plane;
	}
	planesToDelete.clear();
}

}
