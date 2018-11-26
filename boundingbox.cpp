#include "boundingbox.h"
#include "ray.h"
#include "vec3.h"
#include "intersectdata.h"

#include <iostream>
#include <cmath>

namespace RayTracer {

BoundingBox::BoundingBox(Scene * const _scene, const Vec3& _position, const Vec3& _dimensions) : RayInteractable(_scene, _position, Vec3(0,0,0), true, false) {
	setDimensions(_dimensions);
}

BoundingBox::~BoundingBox() {}

Vec3 BoundingBox::getDimensions() const {
	return dimensions;
}

void BoundingBox::setPosition(const Vec3& _position) {
	min = _position - (dimensions*0.5);
	max = _position + (dimensions*0.5);
	return Entity::setPosition(_position);
}

void BoundingBox::setDimensions(const Vec3& _dimensions) {
	dimensions = _dimensions;

	min = getPosition() - (dimensions*0.5);
	max = getPosition() + (dimensions*0.5);
}

bool BoundingBox::testIntersection(const Ray& r, bool testForwards, bool testBackwards) {
	if (!canIntersectRays()) { return false; }
	if (intersect(r,testForwards,testBackwards)) { return true; }
	return false;
}

void BoundingBox::expand(BoundingBox * const bb) {
	Vec3 bbDim = bb->getDimensions();
	Vec3 bbPos = bb->getPosition();
	Vec3 bbMax = bbPos + 0.5*bbDim;
	Vec3 bbMin = bbPos - 0.5*bbDim;

	double maxX = std::max(max.getX(),bbMax.getX());
	double maxY = std::max(max.getY(),bbMax.getY());
	double maxZ = std::max(max.getZ(),bbMax.getZ());

	double minX = std::min(min.getX(),bbMin.getX());
	double minY = std::min(min.getY(),bbMin.getY());
	double minZ = std::min(min.getZ(),bbMin.getZ());

	Vec3 newMax(maxX,maxY,maxZ);
	Vec3 newMin(minX,minY,minZ);

	setPosition(0.5*Vec3(maxX + minX, maxY + minY, maxZ + minZ));
	setDimensions(Vec3(maxX - minX, maxY - minY, maxZ - minZ));
}

int BoundingBox::longestAxis() const {
	// returns: 0 = x, 1 = y, 2 = z
	if (dimensions.getX() > dimensions.getY() && dimensions.getX() > dimensions.getZ()) { return 0; }
	if (dimensions.getY() > dimensions.getX() && dimensions.getY() > dimensions.getZ()) { return 1; }
	if (dimensions.getZ() > dimensions.getX() && dimensions.getZ() > dimensions.getY()) { return 2; }
	return 0;
}

BoundingBox * BoundingBox::copy() const {
	BoundingBox * bb = new BoundingBox(getScene(),getPosition(),getDimensions());
	return bb;
}

std::vector<Vec3> BoundingBox::getMaxCoords() const {
	return std::vector<Vec3>{min,max};
}

std::experimental::optional<IntersectData> BoundingBox::intersect(const Ray& r, bool testForwards, bool testBackwards) const {
	// https://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/
	// todo: forwards/backwards

	double t1 = (min.getX() - r.getPosition().getX())*r.getDirection().getInvX();
	double t2 = (max.getX() - r.getPosition().getX())*r.getDirection().getInvX();

	double tmin = std::min(t1,t2);
	double tmax = std::max(t1,t2);

        t1 = (min.getY() - r.getPosition().getY())*r.getDirection().getInvY();
        t2 = (max.getY() - r.getPosition().getY())*r.getDirection().getInvY();
        tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
        tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));

        t1 = (min.getZ() - r.getPosition().getZ())*r.getDirection().getInvZ();
        t2 = (max.getZ() - r.getPosition().getZ())*r.getDirection().getInvZ();
        tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
        tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));

	if (tmax >= std::max(tmin, 0.0)) {
		IntersectData out;
		return std::experimental::optional<IntersectData>(out);
	}

	return std::experimental::nullopt;
}

}
