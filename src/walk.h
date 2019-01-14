#ifndef WALK_H_
#define WALK_H_

#include "leg.h"
#include "vec.h"

// step_time has to be in range [0, 1[, at 1 all legs have taken one step
void update_legs(Leg *legs, vec3 direction, float step_time);

#endif
