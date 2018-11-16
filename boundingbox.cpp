#include "boundingbox.h"

namespace RayTracer {

BoundingBox::BoundingBox(Scene * const _scene, const Vec3& _position, const Vec3& _angle, const Vec3& _dimensions) : Box(_scene, _position, _angle, _dimensions, true, false) {}

}
