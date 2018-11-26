#include "surface.h"
#include "intersectdata.h"

namespace RayTracer {

Surface::Surface(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : BoundableEntity(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {
	ColorData colorData;
	colorData.color = Vec3(0,0,0);
	setColorData(colorData);
}

Surface::~Surface() {}

void Surface::setColorData(const ColorData& _colorData) {
	colorDataFunc = [=](const Vec3& _position) -> ColorData { return colorDataFuncSimple(); };
	colorDataFuncSimple = [=]() -> ColorData { return _colorData; };
}

void Surface::setColorData(std::function<ColorData(const Vec3&)> _colorDataFunc) {
	colorDataFunc = _colorDataFunc;
}

ColorData Surface::getColorData(const Vec3& _position) const {
	return colorDataFunc(_position);
}

ColorData Surface::getColorData() const {
	return colorDataFunc(Vec3(0,0,0));
}

std::experimental::optional<IntersectData> Surface::intersect(const Ray& _r, bool testForwards, bool testBackwards) const {
	return (getIntersectData(_r,testForwards,testBackwards));
}

}
