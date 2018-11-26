#include "plane.h"
#include "ray.h"
#include "consts.h"

#include <cmath>

namespace RayTracer {

Plane::Plane(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 & worldAng, double width, double height) : Surface(scene, worldPos, worldAng) {
	this->setDimensions(width, height);
}

Vec3 Plane::getPointOnSurface(double u, double v) const {
	return toWorld(Vec3(u,v,0));
}

std::experimental::optional<Vec3> Plane::getNorm(const Vec3 &worldPos) const {
	if (this->isInPlane(worldPos)) { return std::experimental::optional<Vec3>(this->up()); }
	return std::experimental::nullopt;
}

std::experimental::optional<IntersectData> Plane::intersectRay(const Ray &r) const {
	Vec3 hitPos = Vec3(0,0,0);
	Vec3 point = r.getPos();
	Vec3 direction = r.getDirection();

	if (isInPlane(point)) { hitPos = point; } else {
		double numerator = signedDistToPlane(point);
		double denominator = direction.dot(this->up());
		if (denominator == 0) { return std::experimental::nullopt; }

		double lambda = numerator/denominator;
		hitPos = point + lambda*direction;
	}

	double dV_width = std::abs(hitPos.dot( this->right() ));
	double dV_height = std::abs(hitPos.dot( this->forward() ));

	if (dV_width*2 > getWidth() + GLOBAL_SETTING_RAY_PRECISION) { return std::experimental::nullopt; }
	if (dV_height*2 > getHeight() + GLOBAL_SETTING_RAY_PRECISION) { return std::experimental::nullopt; }

	IntersectData intersectData;
	intersectData.surface = this;
	intersectData.hitPos = hitPos;
	intersectData.colorData = getColor(intersectData.hitPos);
	intersectData.hitNorm = this->up();

	return std::experimental::optional<IntersectData>(intersectData);
}

std::vector<Vec3> Plane::getCorners() const {
	Vec3 corner1 = this->toWorld(Vec3(height/2,width/2,0));
	Vec3 corner2 = this->toWorld(Vec3(height/2,-width/2,0));
	Vec3 corner3 = this->toWorld(Vec3(-height/2,width/2,0));
	Vec3 corner4 = this->toWorld(Vec3(-height/2,-width/2,0));

	double maxX = std::max( std::max(corner1.getX(),corner2.getX()), std::max(corner3.getX(),corner4.getX()) );
	double maxY = std::max( std::max(corner1.getY(),corner2.getY()), std::max(corner3.getY(),corner4.getY()) );
	double maxZ = std::max( std::max(corner1.getZ(),corner2.getZ()), std::max(corner3.getZ(),corner4.getZ()) );

	double minX = std::min( std::min(corner1.getX(),corner2.getX()), std::min(corner3.getX(),corner4.getX()) );
	double minY = std::min( std::min(corner1.getY(),corner2.getY()), std::min(corner3.getY(),corner4.getY()) );
	double minZ = std::min( std::min(corner1.getZ(),corner2.getZ()), std::min(corner3.getZ(),corner4.getZ()) );

	return std::vector<Vec3>{ Vec3(minX,minY,minZ), Vec3(maxX,maxY,maxZ) };
}

void Plane::setDimensions(double width, double height) {
	this->width = width;
	this->height = height;
}

double Plane::getWidth() const {
	return this->width;
}

double Plane::getHeight() const {
	return this->height;
}

bool Plane::isInsidePlane(const Vec3 &worldPos) const {
	// "inside" plane if it's on the opposite side to the outward pointing norm
	return (signedDistToPlane(worldPos) >= -GLOBAL_SETTING_RAY_PRECISION);
}

bool Plane::isInPlane(const Vec3 &worldPos) const {
	return (distToPlane(worldPos) <= GLOBAL_SETTING_RAY_PRECISION);
}

double Plane::distToPlane(const Vec3 &worldPos) const {
	return std::abs(this->signedDistToPlane(worldPos));
}

double Plane::signedDistToPlane(const Vec3 &worldPos) const {
	return (this->getPos() - worldPos).dot(this->up());
}

}

