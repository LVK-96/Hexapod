#ifndef LEG_H
#define LEG_H

#include <Servo.h>

#include "vec.h"

class Leg {
public:
    // direction is the angle the leg is pointed in
    void init(vec3 pins, vec3 rest_point, vec3 angle_calibration, vec3 angle_sign, float direction);
    
    void set_rel_position(vec3 pos);
    void set_angles(vec3 angles);

private:
    Servo servo[3];
    vec3 rest_point;
    vec3 angle_calibration;
    vec3 angle_sign;
    float rotation_mat[2][2];
};

#endif

