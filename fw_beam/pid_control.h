#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include <stdint.h>

class PIDController {
private:
    double kp;
    double ki;
    double kd;
    float dt;
    double integral;
    double target;
    double out_min;
    double out_max;
    double last_time;
    double last_error;
public:
    PIDController(double kp, double ki, double kd, double dt, double target, double out_min, double out_max);
    bool calculate(uint16_t *input, double *response);
};

#endif // PID_CONTROL_H
