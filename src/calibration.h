#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <math.h>

// length of the leg parts, counted from the tip of the leg
#define LEG_1_LENGTH 110
#define LEG_2_LENGTH 107
#define LEG_3_LENGTH 80

#define MAX_STEP_LENGTH 30
#define MAX_WALKING_SPEED 0.001f
#define MAX_DRIVING_SPEED 255

#define SERVO_MIN 550
#define SERVO_MAX 2450
#define SERVO_NEUTRAL 1500
#define SERVO_2_PI_RADIANS ((SERVO_MAX - SERVO_MIN) / M_PI)

#endif
