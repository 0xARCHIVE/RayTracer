#ifndef BOX_H
#define BOX_H

namespace RayTracer {

class Box : public ConvexPolygon {
	private:
		Vec3 dimensions;
	public:
		Box(std::shared_ptr<const Scene> scene, const Vec3 &worldPos, const Vec3 &worldAng, const Vec3 &dimensions);
		virtual ~Box();

		void setDimensions(const Vec3 &dimensions);
		Vec3 getDimensions() const;
};

}

#endif
