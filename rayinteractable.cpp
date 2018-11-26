#include "rayinteractable.h"
#include "intersectdata.h"

namespace RayTracer {

RayInteractable::RayInteractable(Scene * const _scene) : Entity(_scene, Vec3(0,0,0), Vec3(0,0,0)) {}

RayInteractable::RayInteractable(Scene * const _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Entity(_scene, _position, _angle) {
	setIntersectRays(_canIntersectRays);
	setGenerateRays(_canGenerateRays);
}

std::experimental::optional<IntersectData> RayInteractable::intersect(const Ray& _r, bool testForwards, bool testBackwards) const {
	return std::experimental::nullopt;
}

bool RayInteractable::canIntersectRays() const {
	return flag_canIntersectRays;
}

bool RayInteractable::canGenerateRays() const {
	return flag_canGenerateRays;
}

void RayInteractable::setIntersectRays(bool _canIntersectRays) {
	flag_canIntersectRays = _canIntersectRays;
}

void RayInteractable::setGenerateRays(bool _canGenerateRays) {
	flag_canGenerateRays = _canGenerateRays;
}

}
