#include "boundingbox.h"

BoundingBox::BoundingBox(const Scene* _scene, const Vec3& _position, const Vec3& _angle) : Box(_scene,_position, _angle, true, false) {}
