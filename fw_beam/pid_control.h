#ifndef PID_CONTROL_H
#define PID_CONTROL_H

class PIDController {
private:
    double kp;
    double ki;
    double kd;
    unsigned long dt;
    unsigned long integral;
    double target;
    double out_min;
    double out_max;
    unsigned long last_time;
    double last_input;
public:
    PIDController(double kp, double ki, double kd, double dt, double target, double out_min, double out_max);
    bool calculate(double *input, double *response);
};

#endif // PID_CONTROL_H
