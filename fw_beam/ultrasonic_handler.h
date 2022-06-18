#ifndef ULTRASONIC_HANDLER_H
#define ULTRASONIC_HANDLER_H

#include <stdint.h>

class UltrasonicHandler {
private:
    uint8_t trigger_pin;
    uint8_t echo_pin;
    double distance;
    void init();
public:
    UltrasonicHandler(uint8_t trigger_pin, uint8_t echo_pin);
    double get_distance_cm();
};

#endif // ULTRASONIC_HANDLER_H
