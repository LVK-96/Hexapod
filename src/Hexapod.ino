#include "calibration.h"
#include "leg.h"
#include "walk.h"
#include "motor.h"

#define WALKING 0
#define DRIVING 1

#define TO_RAD (M_PI / 180.f)

Leg legs[6];
Motors motors;

float walk_timer = 0;
unsigned long last_tick_time;
vec3 move_dir;

bool moving = false;
int state = WALKING;

float speed = 0;

void setup()
{
    Serial.begin(115200);

    legs[0].init(vec3( 9, 10, 11), vec3(60, 200, 0), vec3(-500, -400, -150),  vec3( 1,  1,  1), 180);
    legs[1].init(vec3(12, 13, 14), vec3(60, 200, 0), vec3(-100, -300, 200), vec3( 1,  1, -1), 120);
    legs[2].init(vec3(15, 16, 17), vec3(60, 200, 0), vec3(-150, -150, -350),  vec3(-1, -1, -1), 60);
    legs[3].init(vec3(18, 38, 39), vec3(60, 200, 0), vec3(150, -0, -250), vec3(-1, -1, -1), 0);
    legs[4].init(vec3(40, 41, 42), vec3(60, 200, 0), vec3(-300, -350, 50),    vec3( 1,  1,  1), 300);
    legs[5].init(vec3(44, 43, 45), vec3(60, 200, 0), vec3(-100, -300, 100),  vec3(-1, -1,  1), 240);

    motors.init();

    last_tick_time = millis();
}

void loop()
{
    if (Serial.available()) {
        char header[3] = {0, 0, 0};

        Serial.readBytes(header, 3);
        
        if (!strncmp(header, "DIR", 3)) {
            // input from the controller is in range 0-255
            move_dir.x = Serial.parseInt() / 128.f - 1;
            move_dir.z = Serial.parseInt() / 128.f - 1;
            speed = sqrt(move_dir.x * move_dir.x + move_dir.z * move_dir.z);

            // normalize if speed is too high
            if (speed > 1) {
                move_dir.x /= speed;
                move_dir.z /= speed;
                speed = 1;
            }

            if (speed > 0.1f) {
                if (!moving) {
                    moving = true;
                    last_tick_time = millis();
                }
            } else {
                moving = false;
                motors.set_speed(0);
            }

            if (moving && state == DRIVING) {
                motors.set_speed(abs(1));
                motors.set_direction(move_dir.z > 0);

                // TODO add steering

                if (abs(move_dir.x) > 0.1) {
                    
                }
            }
            
        } else if (!strncmp(header, "WLK", 3)) {
            state = WALKING;
            moving = false;
            motors.set_speed(0);
            motors.set_enabled(false);
            
            for (int i = 0; i < 6; i++)
                legs[i].set_rel_position(vec3(0, 0, 0));
            
        } else if (!strncmp(header, "DRV", 3)) {
            state = DRIVING;
            moving = false;
            motors.set_enabled(true);
            motors.set_speed(0);
            
            legs[0].set_angles(vec3(110 * TO_RAD, -70 * TO_RAD, 0));
            legs[3].set_angles(vec3(110 * TO_RAD, -70 * TO_RAD, 0));
            
            legs[1].set_angles(vec3(100 * TO_RAD, 60 * TO_RAD, -65 * TO_RAD));
            legs[2].set_angles(vec3(100 * TO_RAD, 65 * TO_RAD,  53 * TO_RAD));
        
            legs[4].set_angles(vec3(100 * TO_RAD, 60 * TO_RAD, -55 * TO_RAD));
            legs[5].set_angles(vec3(90 * TO_RAD, 75 * TO_RAD,  55 * TO_RAD));

        }
    }

    if (moving) {

        if (state == WALKING) {
            // increase timer
            walk_timer += (millis() - last_tick_time) * MAX_WALKING_SPEED * speed;
            if (walk_timer >= 1) {
                // keep everything after the decimal point
                walk_timer -= floor(walk_timer);
            }
            
            // update last tick time as soon as possible to increase accuracy
            last_tick_time = millis();

            
            update_legs(legs, move_dir, walk_timer);
        }
    }
}
