#include "surface.h"
#include "intersectdata.h"

namespace RayTracer {

Surface::Surface(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Entity(_scene, _position, _angle) , RayInteractable(_canIntersectRays, _canGenerateRays) {
	ColorData colorData;
	colorData.color = Vec3(0,0,0);
	setColorData(colorData);
}

void Surface::setColorData(const ColorData& _colorData) {
	colorDataFunc = [=](const Vec3& _position) -> ColorData { return colorDataFuncSimple(); };
	colorDataFuncSimple = [=]() -> ColorData { return _colorData; };
}

void Surface::setColorData(std::function<ColorData(const Vec3&)> _colorDataFunc) {
	colorDataFunc = _colorDataFunc;
}

ColorData Surface::getColorData(const Vec3& _position) {
	return colorDataFunc(_position);
}

ColorData Surface::getColorData() {
	return colorDataFunc(Vec3(0,0,0));
}

std::experimental::optional<IntersectData> Surface::intersect(const Ray& _r) {
	std::experimental::optional<Vec3> hitPos = getIntersectionPoint(_r);
	if (!hitPos) { return std::experimental::nullopt; }

	std::experimental::optional<Vec3> hitNorm = getHitNorm(hitPos.value());
	if (!hitNorm) { return std::experimental::nullopt; }

	IntersectData intersectData;
	intersectData.surface = this;
	intersectData.hitPos = hitPos.value();
	intersectData.hitNorm = hitNorm.value();

	return std::experimental::optional<IntersectData>{intersectData};
}

}
