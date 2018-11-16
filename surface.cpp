#include "surface.h"

Surface::Surface(const Scene& _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) {
	colorDataFunc = [](const Vec3& _position) -> ColorData { ColorData colorData; return colorData; };	// return default ColorData
}

ColorData Surface::getColorData(const Vec3& _position) {
	return colorDataFunc(_position);
}
