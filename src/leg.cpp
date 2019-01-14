#include "leg.h"

#include <math.h>
#include <Arduino.h>
#include "calibration.h"

void Leg::init(vec3 pins, vec3 rest_point_, vec3 angle_calibration_, vec3 angle_sign_, float direction)
{
    rest_point = rest_point_;
    angle_calibration = angle_calibration_;
    angle_sign = angle_sign_;

    rotation_mat[0][0] = cos(direction / 180.f * PI);
    rotation_mat[0][1] = sin(direction / 180.f * PI);
    rotation_mat[1][0] = -sin(direction / 180.f * PI);
    rotation_mat[1][1] = cos(direction / 180.f * PI);
  
    servo[0].attach(pins.x);
    servo[1].attach(pins.y);
    servo[2].attach(pins.z);

    set_rel_position(vec3());
}

// sets the position relative to the rest point
void Leg::set_rel_position(vec3 pos)
{ 
    // rotate the vector
    vec3 temp = pos;
    pos.x = rotation_mat[0][0] * temp.x + rotation_mat[1][0] * temp.z;
    pos.z = rotation_mat[0][1] * temp.x + rotation_mat[1][1] * temp.z;
    
    pos += rest_point;
  
    // convert to two dimensions
    float px = sqrt(pos.x * pos.x + pos.z * pos.z) - LEG_3_LENGTH;
    float py = pos.y;
  
    float a = sqrt(px * px + py * py);

    // law of cosines
    float angle1 = PI - acos((a * a - LEG_1_LENGTH * LEG_1_LENGTH - LEG_2_LENGTH * LEG_2_LENGTH) / (-2 * LEG_1_LENGTH * LEG_2_LENGTH));

    float theta = atan2(px, py);
    float angle2 = PI / 2 - theta - acos((LEG_2_LENGTH * LEG_2_LENGTH - LEG_1_LENGTH * LEG_1_LENGTH - a * a) / (-2 * LEG_1_LENGTH * a));
  
    float angle3 = atan2(pos.z, pos.x);
    
    servo[0].writeMicroseconds(angle_sign.x * (angle1 * SERVO_2_PI_RADIANS + angle_calibration.x) + SERVO_NEUTRAL);
    servo[1].writeMicroseconds(angle_sign.y * (angle2 * SERVO_2_PI_RADIANS + angle_calibration.y) + SERVO_NEUTRAL);
    servo[2].writeMicroseconds(angle3 * SERVO_2_PI_RADIANS + angle_calibration.z + SERVO_NEUTRAL);
}

void Leg::set_angles(vec3 angles)
{
    servo[0].writeMicroseconds(angle_sign.x * (angles.x * SERVO_2_PI_RADIANS + angle_calibration.x) + SERVO_NEUTRAL);
    servo[1].writeMicroseconds(angle_sign.y * (angles.y * SERVO_2_PI_RADIANS + angle_calibration.y) + SERVO_NEUTRAL);
    servo[2].writeMicroseconds(angles.z * SERVO_2_PI_RADIANS + angle_calibration.z + SERVO_NEUTRAL);
}

