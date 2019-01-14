#include "motor.h"

#include "calibration.h"
#include "Arduino.h"

void Motors::init()
{
    pinMode(MOTOR_DIRECTION_PIN_1, OUTPUT);
    pinMode(MOTOR_DIRECTION_PIN_2, OUTPUT);
    pinMode(MOTOR_ENABLE_PIN, OUTPUT);
    pinMode(MOTOR_SPEED_PIN, OUTPUT);
}

void Motors::set_direction(bool forward)
{
    digitalWrite(MOTOR_DIRECTION_PIN_1, forward ? HIGH : LOW);
    digitalWrite(MOTOR_DIRECTION_PIN_2, forward ? LOW : HIGH);
}

void Motors::set_enabled(bool enabled)
{
    digitalWrite(MOTOR_ENABLE_PIN, enabled ? HIGH : LOW);
}

void Motors::set_speed(float speed)
{
    analogWrite(MOTOR_SPEED_PIN, speed * MAX_DRIVING_SPEED);
}

