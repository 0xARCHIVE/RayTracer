#include "object.h"
#include "scene.h"
#include "boundingbox.h"
#include "consts.h"
#include "intersectdata.h"
#include "scene.h"
#include "kdnode.h"
#include "vec3.h"
#include "ray.h"
#include "surface.h"

#include <algorithm>
#include <iostream>

namespace RayTracer {

Object::Object(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : BoundableEntity(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	kdroot = new KDNode(_scene);
	_scene->addObject(this);
}

Object::~Object() {
	if (kdroot != nullptr) { delete kdroot; }
}

void Object::addSurface(Surface * const _surface) {
	if (_surface == nullptr) { return; }
	surfaces.push_back(_surface);
	addChild(_surface);

	buildKDroot();
}

std::vector<Surface *>& Object::getSurfaces() {
	return surfaces;
}

std::vector<Vec3> Object::getMaxCoords() const {
	// return two corners of BB enclosing convexpolygon
	bool set = false;
	double maxX = 0;
	double maxY = 0;
	double maxZ = 0;
	double minX = 0;
	double minY = 0;
	double minZ = 0;

	for (auto surface : surfaces) {
		std::vector<Vec3> coords = surface->getMaxCoords();
		Vec3 v1 = coords[0];
		Vec3 v2 = coords[1];

		Vec3 minV( std::min(v1.getX(),v2.getX()), std::min(v1.getY(),v2.getY()), std::min(v1.getZ(),v2.getZ())  );
		Vec3 maxV( std::max(v1.getX(),v2.getX()), std::max(v1.getY(),v2.getY()), std::max(v1.getZ(),v2.getZ())  );

		if (!set) {
			minX = minV.getX();
			minY = minV.getY();
			minZ = minV.getZ();

			maxX = maxV.getX();
			maxY = maxV.getY();
			maxZ = maxV.getZ();

			set = true;
			continue;
		}

		maxX = std::max(maxV.getX(), maxX);
		maxY = std::max(maxV.getY(), maxY);
		maxZ = std::max(maxV.getZ(), maxZ);

		minX = std::min(minV.getX(), minX);
		minY = std::min(minV.getY(), minY);
		minZ = std::min(minV.getZ(), minZ);
	}

	return std::vector<Vec3>{ Vec3(maxX,maxY,maxZ), Vec3(minX,minY,minZ) };
}

std::experimental::optional<IntersectData> Object::intersect(const Ray& _r, bool testForwards, bool testBackwards) const {
	return kdroot->intersect(_r,testForwards,testBackwards);
}

void Object::buildKDroot() {
	enableAABB();

	std::vector<Entity*> children = getChildren();
	std::vector<BoundableEntity*> boundableChildren;
	for (auto child : children) {
		boundableChildren.push_back(static_cast<BoundableEntity*>(child));
	}
	KDNode * kdroot_new = kdroot->build(boundableChildren);
	delete kdroot;
	kdroot = kdroot_new;
}

}
