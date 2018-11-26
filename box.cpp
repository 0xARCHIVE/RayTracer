#include "box.h"
#include "plane.h"

namespace RayTracer {

Box::Box(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng, const Vec3 &dimensions) : ConvexPolygon(scene, worldPos, worldAng) {
	this->setDimensions(dimensions);

	double depth = dimensions.getX();
	double width = dimensions.getY();
	double height = dimensions.getZ();

	std::shared_ptr<Plane> p1 = std::make_shared<Plane>(scene, toWorld(Vec3(depth/2,0,0)), worldAng + Vec3(90,0,0), width,height);
	std::shared_ptr<Plane> p2 = std::make_shared<Plane>(scene, toWorld(Vec3(-depth/2,0,0)), worldAng + Vec3(-90,0,0), width,height);
	std::shared_ptr<Plane> p3 = std::make_shared<Plane>(scene, toWorld(Vec3(0,width/2,0)), worldAng + Vec3(0,0,-90), depth,height);
	std::shared_ptr<Plane> p4 = std::make_shared<Plane>(scene, toWorld(Vec3(0,-width/2,0)), worldAng + Vec3(0,0,90), depth,height);
	std::shared_ptr<Plane> p5 = std::make_shared<Plane>(scene, toWorld(Vec3(0,0,height/2)), worldAng, width,depth);
	std::shared_ptr<Plane> p6 = std::make_shared<Plane>(scene, toWorld(Vec3(0,0,-height/2)), worldAng + Vec3(0,0,180), width,depth);

	// testing
	ColorData c;
	c.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
	c.emissivity = 1;
	c.reflectivity = 0;
	c.transmissivity = 0;
	c.multiplier = 1;

	ColorData c1 = c;
	ColorData c2 = c;
	ColorData c3 = c;
	ColorData c4 = c;
	ColorData c5 = c;
	ColorData c6 = c;

	c1.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
	c2.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
	c3.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
	c4.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
	c5.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));
	c6.color = Vec3(rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0),rand()/(RAND_MAX+1.0));

	p1->setColor(c1);
	p2->setColor(c2);
	p3->setColor(c3);
	p4->setColor(c4);
	p5->setColor(c5);
	p6->setColor(c6);
	//

	this->addChild(p1);
	this->addChild(p2);
	this->addChild(p3);
	this->addChild(p4);
	this->addChild(p5);
	this->addChild(p6);

	p1->setIntersectRays(true);
	p2->setIntersectRays(true);
	p3->setIntersectRays(true);
	p4->setIntersectRays(true);
	p5->setIntersectRays(true);
	p6->setIntersectRays(true);

	p1->setGenerateRays(true);
	p2->setGenerateRays(true);
	p3->setGenerateRays(true);
	p4->setGenerateRays(true);
	p5->setGenerateRays(true);
	p6->setGenerateRays(true);
}

Box::~Box() {}

void Box::setDimensions(const Vec3 &dimensions) {
	this->dimensions = dimensions;
}

Vec3 Box::getDimensions() const {
	return this->dimensions;
}

}
