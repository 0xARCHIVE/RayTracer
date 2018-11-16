#include "rayinteractable.h"

namespace RayTracer {

RayInteractable::RayInteractable() {}

RayInteractable::RayInteractable(bool _canIntersectRays, bool _canGenerateRays) {
	setIntersectRays(_canIntersectRays);
	setGenerateRays(_canGenerateRays);
}

bool RayInteractable::canIntersectRays() {
	return flag_canIntersectRays;
}

bool RayInteractable::canGenerateRays() {
	return flag_canGenerateRays;
}

void RayInteractable::setIntersectRays(bool _canIntersectRays) {
	flag_canIntersectRays = _canIntersectRays;
}

void RayInteractable::setGenerateRays(bool _canGenerateRays) {
	flag_canGenerateRays = _canGenerateRays;
}

}
