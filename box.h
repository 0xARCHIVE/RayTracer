#ifndef BOX_H
#define BOX_H

namespace RayTracer {

class Box : public Surface {
	public:
		Box(const Scene& _scene, const Vec3& _position, const Vec3& _angle, bool _canIntersectRays, bool _canGenerateRays) : Surface(_scene, _position, _angle, _canIntersectRays, _canGenerateRays) {}
		Vec3 getIntersectionPoint(const Ray& _r);
		Vec3 getHitNorm(const Vec3& _position);
};

}

#endif
