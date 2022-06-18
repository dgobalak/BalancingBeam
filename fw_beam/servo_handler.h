#ifndef SERVO_HANDLER_H
#define SERVO_HANDLER_H

#include <stdint.h>

#define INITIAL_ANGLE 90
#define SERVO_MIN_DELAY_US 544
#define SERVO_MAX_DELAY_US 2400

class ServoHandler {
private:
    uint8_t servo_pin;
    uint16_t curr_angle;
    uint16_t angle_min;
    uint16_t angle_max;
    void init();
    void move_pwm(uint16_t angle);
    uint16_t clamp_angle(int16_t angle);
public:
    ServoHandler(uint8_t pin, int16_t angle_min, int16_t angle_max);
    void move(uint16_t angle);
    uint16_t get_angle();
};

#endif // SERVO_HANDLER_H
