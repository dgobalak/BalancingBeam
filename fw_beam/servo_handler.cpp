#include "servo_handler.h"

#include <stdlib.h>
#include <Arduino.h>
#include <stdint.h>

ServoHandler::ServoHandler(uint8_t pin, int16_t angle_min, int16_t angle_max) {
    this->servo_pin = pin;
    this->angle_min = angle_min;
    this->angle_max = angle_max;
    this->curr_angle = INITIAL_ANGLE;

    this->init();
}

void ServoHandler::init() {
    pinMode(servo_pin, OUTPUT);
    this->move_pwm(INITIAL_ANGLE);
}

void ServoHandler::move(uint16_t angle) {
    angle = this->clamp_angle(angle);
    this->move_pwm(angle);
}

void ServoHandler::move_pwm(uint16_t angle) {
    uint32_t delay_us = map(angle, angle_min, angle_max, SERVO_MIN_DELAY_US, SERVO_MAX_DELAY_US);
    for (uint16_t i = this->curr_angle; i < angle; i++) {
        digitalWrite(servo_pin, HIGH);
        delayMicroseconds(delay_us);
        digitalWrite(servo_pin, LOW);
        delay(10);
    }
    this->curr_angle = angle;
}

uint16_t ServoHandler::get_angle() {
    return this->curr_angle;
}

uint16_t ServoHandler::clamp_angle(int16_t angle) {
    return min(this->angle_max, max(angle, this->angle_min));
}