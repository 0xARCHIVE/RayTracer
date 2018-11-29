#ifndef CONSTS_H
#define CONSTS_H

namespace RayTracer {

const float GLOBAL_SETTING_RAY_PRECISION = 0.0000000000001;	// how close a ray a ray has to be to a surface before it is considered intersecting
const int GLOBAL_SETTING_RAY_MAX_LIFE = 1;		// how many times a ray will recurse
const float GLOBAL_SETTING_RAY_SPREAD = 0;		// how much rays should scatter at each step (degrees)
const int GLOBAL_SETTING_RAY_NUM_SPAWN = 10;		// how many rays should be spawned at each step

}

#endif
