#ifndef OBJECT_H
#define OBJECT_H

#include "entity.h"
#include "boundingbox.h"

namespace RayTracer {

class Object : public Entity {
	private:
		BoundingBox boundingBox;
};

}

#endif
