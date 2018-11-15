#ifndef SURFACE_H
#define SURFACE_H

#include "entity.h"
#include "rayintersectable.h"

namespace RayTracer {

class Surface : public Entity, public RayIntersectable {
};

}

#endif
