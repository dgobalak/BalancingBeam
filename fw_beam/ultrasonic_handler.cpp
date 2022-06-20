#include "ultrasonic_handler.h"

#include <stdint.h>
#include <Arduino.h>

UltrasonicHandler::UltrasonicHandler(uint8_t trigger_pin, uint8_t echo_pin) {
    this->trigger_pin = trigger_pin;
    this->echo_pin = echo_pin;

    this->init();
}

void UltrasonicHandler::init() {
    pinMode(this->trigger_pin, OUTPUT);
    pinMode(this->echo_pin, INPUT);
}

double UltrasonicHandler::get_distance_cm() {
    // Clears the trigPin
    digitalWrite(this->trigger_pin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(this->trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trigger_pin, LOW);

    this->distance = pulseIn(this->echo_pin, HIGH) * 0.034 / 2;

    #ifdef DEBUG
    Serial.println(String(this->distance) + " cm");
    #endif

    return this->distance;
}
