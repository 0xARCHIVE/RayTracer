#include "boundingbox.h"
#include "ray.h"
#include "intersectdata.h"
#include "entity.h"

#include <cmath>

namespace RayTracer {

BoundingBox::BoundingBox(const Vec3 &worldPos, const Vec3 &dimensions) {
	this->setPos(worldPos);
	this->setDimensions(dimensions);
}

void BoundingBox::setPos(const Vec3 &worldPos) {
	this->worldPos = worldPos;
	this->minCorner = this->getPos() - this->getDimensions()*0.5;
	this->maxCorner = this->getPos() + this->getDimensions()*0.5;
}

Vec3 BoundingBox::getPos() const {
	return this->worldPos;
}

Vec3 BoundingBox::getDimensions() const {
	return this->dimensions;
}

void BoundingBox::setDimensions(const Vec3 &dimensions) {
	this->dimensions = dimensions;
	this->setPos(this->getPos());
}

std::vector<Vec3> BoundingBox::getCorners() const {
	return std::vector<Vec3>{ this->minCorner, this->maxCorner };
}

void BoundingBox::setCorners(const Vec3 &v1, const Vec3 &v2) {
	Vec3 AABBmin;
	Vec3 AABBmax;

	AABBmin.setX( std::min(v1.getX(),v2.getX()) );
	AABBmin.setY( std::min(v1.getY(),v2.getY()) );
	AABBmin.setZ( std::min(v1.getZ(),v2.getZ()) );

	AABBmax.setX( std::max(v1.getX(),v2.getX()) );
	AABBmax.setY( std::max(v1.getY(),v2.getY()) );
	AABBmax.setZ( std::max(v1.getZ(),v2.getZ()) );

	this->minCorner = AABBmin;
	this->maxCorner = AABBmax;

	this->dimensions = (AABBmax - AABBmin);
	this->worldPos = (AABBmax + AABBmin)*0.5;
}

int BoundingBox::getLongestAxis() const {
	// returns: 0 = x, 1 = y, 2 = z
	if (dimensions.getX() > dimensions.getY() && dimensions.getX() > dimensions.getZ()) { return 0; }
	if (dimensions.getY() > dimensions.getX() && dimensions.getY() > dimensions.getZ()) { return 1; }
	if (dimensions.getZ() > dimensions.getX() && dimensions.getZ() > dimensions.getY()) { return 2; }
	return 0;
}

void BoundingBox::expandToInclude(const BoundingBox &aabb) {
	std::vector<Vec3> corners = this->getCorners();
	std::vector<Vec3> AABBcorners = aabb.getCorners();

	Vec3 v1 = corners[0];
	Vec3 v2 = corners[1];
	Vec3 AABBv1 = AABBcorners[0];
	Vec3 AABBv2 = AABBcorners[1];

	if (v1 == v2) { this->setCorners(AABBv1,AABBv2); return; }

	Vec3 AABBmax;
	Vec3 AABBmin;

	AABBmin.setX( std::min( std::min(AABBv1.getX(),AABBv2.getX()), std::min(v1.getX(), v2.getX()) ));
	AABBmin.setY( std::min( std::min(AABBv1.getY(),AABBv2.getY()), std::min(v1.getY(), v2.getY()) ));
	AABBmin.setZ( std::min( std::min(AABBv1.getZ(),AABBv2.getZ()), std::min(v1.getZ(), v2.getZ()) ));

	AABBmax.setX( std::max( std::max(AABBv1.getX(),AABBv2.getX()), std::max(v1.getX(), v2.getX()) ));
	AABBmax.setY( std::max( std::max(AABBv1.getY(),AABBv2.getY()), std::max(v1.getY(), v2.getY()) ));
	AABBmax.setZ( std::max( std::max(AABBv1.getZ(),AABBv2.getZ()), std::max(v1.getZ(), v2.getZ()) ));

	this->setCorners(AABBmin,AABBmax);
}

void BoundingBox::expandToInclude(const Vec3 &corner1, const Vec3 &corner2) {
	BoundingBox aabb;
	aabb.setCorners(corner1,corner2);

	this->expandToInclude(aabb);
}

void BoundingBox::expandToInclude(const std::vector<std::shared_ptr<Entity>>& ents) {
	for (auto ent : ents) {
		this->expandToInclude(ent->getAABB());
	}
}

void BoundingBox::copy(const BoundingBox &aabb) {
	std::vector<Vec3> corners = aabb.getCorners();
	this->setCorners(corners[0],corners[1]);
}

std::unique_ptr<IntersectData> BoundingBox::intersectRay(const Ray &r) const {
	// https://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/
	std::vector<Vec3> corners = this->getCorners();
	Vec3 min = corners[0];
	Vec3 max = corners[1];

	if (min == max) { return nullptr; }

	double t1 = (min.getX() - r.getPos().getX())*r.getDirection().getInvX();
	double t2 = (max.getX() - r.getPos().getX())*r.getDirection().getInvX();

	double tmin = std::min(t1,t2);
	double tmax = std::max(t1,t2);

        t1 = (min.getY() - r.getPos().getY())*r.getDirection().getInvY();
        t2 = (max.getY() - r.getPos().getY())*r.getDirection().getInvY();
        tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
        tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));

        t1 = (min.getZ() - r.getPos().getZ())*r.getDirection().getInvZ();
        t2 = (max.getZ() - r.getPos().getZ())*r.getDirection().getInvZ();
        tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
        tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));

	if (tmax >= std::max(tmin, 0.0)) { return std::make_unique<IntersectData>(); }
	return nullptr;
}

}
