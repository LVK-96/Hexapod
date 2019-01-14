#include "walk.h"

#include "calibration.h"
#include "Arduino.h"

// lookup table for leg movement during a step
// the coordinates are in the same plane as the walking direction
const static vec3 step_lookup[33] = {
  vec3( 0.000f,    0     , 0),
  vec3(-0.100f,    0     , 0),
  vec3(-0.200f,    0     , 0),
  vec3(-0.300f,    0     , 0),
  vec3(-0.400f,    0     , 0),
  vec3(-0.500f,    0     , 0),
  vec3(-0.600f,    0     , 0),
  vec3(-0.700f,    0     , 0),
  vec3(-0.800f,    0     , 0),
  vec3(-0.900f,    0     , 0),
  vec3(-1.000f,    0     , 0),
  vec3(-0.833f,   -0.305f, 0),
  vec3(-0.666f,   -0.555f, 0),
  vec3(-0.500f,   -0.750f, 0),
  vec3(-0.333f,   -0.888f, 0),
  vec3(-0.333f,   -0.972f, 0),
  vec3( 0     ,   -1.000f, 0),
  vec3( 0.333f,   -0.972f, 0),
  vec3( 0.333f,   -0.888f, 0),
  vec3( 0.500f,   -0.555f, 0),
  vec3( 0.666f,   -0.305f, 0),
  vec3( 0.833f,    0     , 0),
  vec3( 1.000f,    0     , 0),
  vec3( 0.900f,    0     , 0),
  vec3( 0.800f,    0     , 0),
  vec3( 0.700f,    0     , 0),
  vec3( 0.600f,    0     , 0),
  vec3( 0.500f,    0     , 0),
  vec3( 0.400f,    0     , 0),
  vec3( 0.300f,    0     , 0),
  vec3( 0.200f,    0     , 0),
  vec3( 0.100f,    0     , 0),
  vec3( 0     ,    0     , 0),
};

vec3 lerp_lookup(float step_time)
{
    int step_index = step_time * 32;
    return step_lookup[step_index] + (step_lookup[step_index + 1] - step_lookup[step_index])
                                   * (step_time * 32.f - step_index);
}

// step_time has to be in range [0, 1[, at 1 all legs have taken one step
void update_legs(Leg *legs, vec3 direction, float step_time)
{
    // odd legs are 0.5 behind
    float odd_step_time = (step_time > 0.5) ? (step_time - 0.5f) : (step_time + 0.5f);
    
    // lerp between two values
    vec3 even_step_length = lerp_lookup(step_time) * MAX_STEP_LENGTH;
    vec3 odd_step_length = lerp_lookup(odd_step_time) * MAX_STEP_LENGTH;

    vec3 even_leg_pos = vec3(direction.x * even_step_length.x, even_step_length.y * 2, direction.z * even_step_length.x);
    vec3  odd_leg_pos = vec3(direction.x *  odd_step_length.x,  odd_step_length.y * 2, direction.z *  odd_step_length.x);

    for (int i = 0; i < 6; i += 2)
      legs[i].set_rel_position(even_leg_pos);

    for (int i = 1; i < 6; i += 2)
      legs[i].set_rel_position( odd_leg_pos);
}

