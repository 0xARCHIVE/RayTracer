#include "surface.h"
#include "intersectdata.h"

namespace RayTracer {

Surface::Surface(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Entity(_scene, _position, _angle) , RayInteractable(_canIntersectRays, _canGenerateRays) {
	colorDataFunc = [](const Vec3& _position) -> ColorData { ColorData colorData; return colorData; };	// return default ColorData
}

ColorData Surface::getColorData(const Vec3& _position) {
	return colorDataFunc(_position);
}

std::experimental::optional<IntersectData> Surface::intersect(const Ray& _r) {
	std::experimental::optional<Vec3> hitPos = getIntersectionPoint(_r);
	if (!hitPos) { return std::experimental::nullopt; }

	std::experimental::optional<Vec3> hitNorm = getHitNorm(hitPos.value());
	if (!hitNorm) { return std::experimental::nullopt; }

	ColorData colorData = getColorData(hitPos.value());

	IntersectData intersectData;
	intersectData.surface = this;
	intersectData.colorData = colorData;
	intersectData.hitPos = hitPos.value();
	intersectData.hitNorm = hitNorm.value();

	return std::experimental::optional<IntersectData>{intersectData};
}

}
