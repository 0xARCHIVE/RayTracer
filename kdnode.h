#ifndef KDNODE_H
#define KDNODE_H

#include "boundableentity.h"

#include <vector>
#include <experimental/optional>

namespace RayTracer {

class IntersectData;
class BoundingBox;
class Scene;

class KDNode : public BoundableEntity {
	public:
		KDNode * left;
		KDNode * right;
		std::vector<BoundableEntity *> ents;

		KDNode(Scene * const_scene);
		~KDNode();
		KDNode * build(const std::vector<BoundableEntity *>& ents);
		virtual std::experimental::optional<IntersectData> intersect(const Ray& _r, bool testForwards = true, bool testBackwards = false) const override;
};

}

#endif
