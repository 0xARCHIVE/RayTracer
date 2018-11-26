#include "surface.h"

namespace RayTracer {

Surface::Surface(std::shared_ptr<Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng) : Entity(scene, worldPos, worldAng) {
	ColorData colorData;
	colorData.color = Vec3(0,0,0);
	this->setColor(colorData);
}

Surface::~Surface() {}

ColorData Surface::getColor() const {
	return this->colorFunc(Vec3(0,0,0));
}

ColorData Surface::getColor(const Vec3 &worldPos) const {
	return this->colorFunc(worldPos);
}

void Surface::setColor(const ColorData &color) {
	this->colorFunc = [=](const Vec3 &worldPos) -> ColorData { return colorFunc_constant(); };
	this->colorFunc_constant = [=]() -> ColorData { return color; };
}

void Surface::setColor(std::function<ColorData(const Vec3& worldPos)> colorFunc) {
	this->colorFunc = colorFunc;
}

}
