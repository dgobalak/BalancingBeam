#include "ultrasonic_handler.h"
#include "lp_filter.h"
#include "servo_handler.h"

#include <stdint.h>

const uint8_t ultrasonic_echo_pin = 7;
const uint8_t ultrasonic_trigger_pin = 8;
const uint8_t servo_pin = 9;

const double lp_filter_alpha = 0.05;

ServoHandler servo(servo_pin, 0, 180);
//UltrasonicHandler ultrasonic(ultrasonic_trigger_pin, ultrasonic_echo_pin);
//LpFilter lp_filter(lp_filter_alpha);

void setup() {
    Serial.begin(9600); // Starts the serial communication
}
void loop() {
//    double filtered_distance = lp_filter.get_filtered_value( ultrasonic.get_distance_cm() );
//    Serial.println(filtered_distance);

    int pos;
    for (pos = 20; pos <= 160; pos += 1) { // goes from 0 degrees to 180 degrees
      servo.move(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 160; pos >= 20; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo.move(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
}
