#include "rayinteractable.h"

RayInteractable::RayInteractable() {}

RayInteractable::RayInteractable(bool _canIntersectRays, bool _canGenerateRays) {
	setIntersectRays(canIntersectRays);
	setGenerateRays(canGenerateRays);
}

bool RayInteractable::canIntersectRays() {
	return canIntersectRays;
}

bool RayInteractable::canGenerateRays() {
	return canGenerateRays();
}

void setIntersectRays(bool _canIntersectRays) {
	canIntersectRays = _canIntersectRays;
}

void setGenerateRays(bool _canGenerateRays) {
	canGenerateRays = _canGenerateRays;
}
