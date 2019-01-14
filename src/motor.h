#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_DIRECTION_PIN_1 20
#define MOTOR_DIRECTION_PIN_2 19
#define MOTOR_ENABLE_PIN      21
#define MOTOR_SPEED_PIN       24

class Motors {
public:
    void init();
    void set_direction(bool forward);
    void set_enabled(bool enabled);
    void set_speed(float speed);
};

#endif
