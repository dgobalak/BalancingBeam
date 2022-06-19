#include "ultrasonic_handler.h"
#include "lp_filter.h"
#include "servo_handler.h"
#include "pid_control.h"
#include "mpu6050.h"

#include <stdint.h>
#include <Wire.h>

const uint8_t ultrasonic_echo_pin = 7;
const uint8_t ultrasonic_trigger_pin = 8;
const uint8_t servo_pin = 9;

const double lp_filter_alpha = 0.05;

int16_t acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z;
double temp;

//ServoHandler servo(servo_pin, 0, 180);
//UltrasonicHandler ultrasonic(ultrasonic_trigger_pin, ultrasonic_echo_pin);
//LpFilter lp_filter(lp_filter_alpha);
//MPU6050 mpu;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Wire.begin();
//  mpu.wakeup();
}
void loop() {
  //    double filtered_distance = lp_filter.get_filtered_value( ultrasonic.get_distance_cm() );
  //    Serial.println(filtered_distance);

  //    int pos;
  //    for (pos = 20; pos <= 160; pos += 1) { // goes from 0 degrees to 180 degrees
  //      servo.move(pos);              // tell servo to go to position in variable 'pos'
  //      delay(15);                       // waits 15ms for the servo to reach the position
  //    }
  //    for (pos = 160; pos >= 20; pos -= 1) { // goes from 180 degrees to 0 degrees
  //      servo.move(pos);              // tell servo to go to position in variable 'pos'
  //      delay(15);                       // waits 15ms for the servo to reach the position
  //    }

//  mpu.read_all_data(&acc_x, &acc_y, &acc_z, &gyro_x, &gyro_y, &gyro_z, &temp);
//  Serial.print("aX = "); Serial.print(mpu.convert_int16_to_str(acc_x));
//  Serial.print(" | aY = "); Serial.print(mpu.convert_int16_to_str(acc_y));
//  Serial.print(" | aZ = "); Serial.print(mpu.convert_int16_to_str(acc_z));
//  Serial.print(" | tmp = "); Serial.print(temp);
//  Serial.print(" | gX = "); Serial.print(mpu.convert_int16_to_str(gyro_x));
//  Serial.print(" | gY = "); Serial.print(mpu.convert_int16_to_str(gyro_y));
//  Serial.print(" | gZ = "); Serial.print(mpu.convert_int16_to_str(gyro_z));
//  Serial.println();
//  delay(1000);
}
