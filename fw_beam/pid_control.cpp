#include "pid_control.h"

#include <Arduino.h>

PIDController::PIDController(double kp, double ki, double kd, double dt, double target, double out_min, double out_max) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->integral = 0;
    this->dt = dt;
    this->target = target;
    this->out_min = out_min;
    this->out_max = out_max;
    this->last_error = 0;
    this->last_time = millis();
}

bool PIDController::calculate(uint16_t *input, double *response) {
    double current_time = millis();
    double dt_ms = current_time - this->last_time;
    if (dt_ms >= this->dt ) {
        double error = this->target - *response;

#if defined(PID_DEBUG) || defined(SYS_DEBUG)
        Serial.println("DT: " + String(dt_ms) + ", PID Error: " + String(error));
#endif

        double proportional = error * this->kp;
        this->integral += ( error * this->dt ) * this->ki;
        double derivative = ( (error - this->last_error) / this->dt ) * this->kd;

#if defined(PID_DEBUG) || defined(SYS_DEBUG)
        Serial.println("Prop: " + String(proportional) + ", Int: " + String(this->integral) + ", Der: " + String(derivative));
#endif
        
        *input = proportional + this->integral + derivative;

        this->last_time = current_time;
        this->last_error = error;
        return true;
    }
    return false;
}
