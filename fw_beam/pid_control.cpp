#include "pid_control.h"

#include <Arduino.h>

PIDController::PIDController(double kp, double ki, double kd, double dt, double target, double out_min, double out_max) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->integral = 0;
    this->last_input = 0;
    this->dt = dt;
    this->target = target;
    this->out_min = out_min;
    this->out_max = out_max;
    this->last_time = millis();
}

bool PIDController::calculate(double *input, double *response) {
    unsigned long current_time = millis();
    unsigned long dt_ms = current_time - this->last_time;
    if (dt_ms >= this->dt ) {
        double error = this->target - *response;

        double proportional = error * this->kp;
        this->integral += error * this->dt * this->ki;
        double derivative = ( (*input - this->last_input) / this->dt ) * this->kd;

        *input = proportional + this->integral + derivative;

        this->last_time = current_time;
        this->last_input = *input;
        return true;
    }
    return false;
}
