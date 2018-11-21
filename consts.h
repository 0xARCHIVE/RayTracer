#ifndef CONSTS_H
#define CONSTS_H

namespace RayTracer {

const float GLOBAL_SETTING_RAY_PRECISION = 0.0001;	// how close a ray a ray has to be to a surface before it is considered intersecting
const int GLOBAL_SETTING_RAY_MAX_LIFE = 20;		// how many times a ray will recurse
const float GLOBAL_SETTING_RAY_SPREAD = 0;		// how much rays should scatter at each step
const int GLOBAL_SETTING_RAY_NUM_SPAWN = 1;		// how many rays should be spawned at each step

}

#endif
